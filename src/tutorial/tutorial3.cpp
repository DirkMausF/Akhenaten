#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/city_message.h"
#include "building/building_granary.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "game/game_events.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

struct tutorial_3 : public tutorial_t {
    virtual int missionid() const override { return 3; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring  overrides);
    virtual xstring goal_text() override;
};

tutorial_3 g_tutorial_3;

void tutorial_3::reset() {
    g_tutorials_flags.tutorial_3.started = 0;
    g_tutorials_flags.tutorial_3.figs_stored = 0;
    g_tutorials_flags.tutorial_3.pottery_made_1 = 0;
    g_tutorials_flags.tutorial_3.pottery_made_2 = 0;
}

void tutorial3_on_filled_granary(event_granary_filled ev) {
    if (g_tutorials_flags.tutorial_3.figs_stored) {
        return;
    }

    auto granary = building_get(ev.bid)->dcast_granary();
    const int figs_stored = granary ? granary->amount(RESOURCE_FIGS) : 0;

    if (figs_stored < g_scenario.vars.get_int("figs_stored", 800)) {
        return;
    }

    events::unsubscribe(&tutorial3_on_filled_granary);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_3.figs_stored = true;
    building_menu_update(tutorial_stage.tutorial_industry);
    messages::popup(MESSAGE_TUTORIAL_INDUSTRY, 0, 0);
}

void tutorial3_on_disease(event_city_disease ev) {
    if (g_tutorials_flags.tutorial_3.disease) {
        return;
    }

    events::unsubscribe(&tutorial3_on_disease);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_3.disease = true;
    building_menu_update(tutorial_stage.tutorial_health);
    messages::popup(MESSAGE_TUTORIAL_BASIC_HEALTHCARE, 0, 0);
}

void tutorial_3::update_step(xstring s) {
    if (s == tutorial_stage.tutorial_health) {
        building_menu_update(s);
        messages::popup(MESSAGE_TUTORIAL_BASIC_HEALTHCARE, 0, 0);
    }

    if (s == tutorial_stage.tutorial_industry) {
        building_menu_update(s);
        messages::popup(MESSAGE_TUTORIAL_INDUSTRY, 0, 0);
    }

    if (s == tutorial_stage.tutorial_gardens) {
        building_menu_update(s);
        messages::popup(MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES, 0, 0);
    }

    const auto advisors = { ADVISOR_LABOR, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION };
    for (auto a : advisors) {
        g_city.set_advisor_available(a, AVAILABLE);
    }
}

void tutorial3_warehouse_pottery_1_check(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_3.pottery_made_1) {
        return;
    } 
    
    const int amount = g_scenario.vars.get_int("pottery_step1_stored", 100);
    if (g_city.resource.yards_stored(RESOURCE_POTTERY) < amount) {
        return;
    }

    events::unsubscribe(&tutorial3_warehouse_pottery_1_check);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_3.pottery_made_1 = true;
    g_tutorials_flags.tutorial_3.pottery_made_year = game.simtime.year;

    messages::popup(MESSAGE_TUTORIAL_FOOD_OR_FAMINE, 0, 0);
}

void tutorial3_warehouse_pottery_2_check(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_3.pottery_made_2) {
        return;
    }
    
    const int amount = g_scenario.vars.get_int("pottery_step2_stored", 200);
    if (g_city.resource.yards_stored(RESOURCE_POTTERY) < amount) {
        return;
    }

    events::unsubscribe(&tutorial3_warehouse_pottery_2_check);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_3.pottery_made_2 = true;
    building_menu_update(tutorial_stage.tutorial_gardens);
    messages::popup(MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES, 0, 0);
}

bool tutorial3_is_success() {
    auto &tut = g_tutorials_flags.tutorial_3;
    const bool may_finish = (tut.figs_stored && tut.pottery_made_1 && tut.pottery_made_2 && tut.disease);
    const int victory_last_action_delay = g_scenario.vars.get_int("victory_last_action_delay", 3);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > victory_last_action_delay;
    return may_finish && some_days_after_last_action;
}

xstring tutorial_3::goal_text() {
    if (!g_tutorials_flags.tutorial_3.figs_stored) {
        return lang_get_xstring(62, 28);
    } 
    
    if (!g_tutorials_flags.tutorial_3.pottery_made_1) {
        return lang_get_xstring(62, 27);
    }
    
    if (!g_tutorials_flags.tutorial_3.pottery_made_1) {
        return "#reach_200_pottery_on_storage";
    }
    
    return lang_get_xstring(62, 26);
}

void tutorial3_hunger_halt_immgrants(event_advance_month ev) {
    if(game.simtime.month >= 5) {
       city_message_post_with_message_delay(MESSAGE_CAT_TUTORIAL3, 1, MESSAGE_TUTORIAL_HUNGER_HALTS_IMMIGRANTS, 1200);
       events::unsubscribe(&tutorial3_hunger_halt_immgrants);
    }
}

void tutorial3_population_cap(city_migration_t& migration) {
    const int population_cap = g_scenario.vars.get_int("pottery_step1_population_cap", 500);
    const int max_pop = (!g_tutorials_flags.tutorial_3.pottery_made_1) ? population_cap : 0;
    migration.population_cap = max_pop;
}

void tutorial_3::init() {
    building_menu_update_if(g_tutorials_flags.tutorial_3.figs_stored, tutorial_stage.tutorial_industry);
    events::subscribe_if(!g_tutorials_flags.tutorial_3.figs_stored, &tutorial3_on_filled_granary);

    building_menu_update_if(g_tutorials_flags.tutorial_3.pottery_made_1, tutorial_stage.tutorial_industry);
    events::subscribe_if(!g_tutorials_flags.tutorial_3.pottery_made_1, &tutorial3_warehouse_pottery_1_check);

    building_menu_update_if(g_tutorials_flags.tutorial_3.pottery_made_2, tutorial_stage.tutorial_gardens);
    events::subscribe_if(!g_tutorials_flags.tutorial_3.pottery_made_2, &tutorial3_warehouse_pottery_2_check);

    building_menu_update_if(g_tutorials_flags.tutorial_3.disease, tutorial_stage.tutorial_health);
    events::subscribe_if(!g_tutorials_flags.tutorial_3.disease, &tutorial3_on_disease);

    if (game.simtime.month < 5) {
        events::subscribe(&tutorial3_hunger_halt_immgrants);
    }

    g_city.victory_state.add_condition(tutorial3_is_success);
    g_city.migration.add_condition(tutorial3_population_cap);
}