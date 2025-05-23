#pragma once

#include <cstdint>

struct event_population_changed { int value; };

struct city_population_t {
    int32_t current;
    int32_t last_day_current;
    int32_t last_year;
    int32_t school_age;
    int32_t academy_age;
    int32_t working_age;
    struct {
        int32_t values[2400];
        int32_t next_index;
        int32_t count;
    } monthly;
    int16_t at_age[100];
    int32_t at_level[20];

    int32_t yearly_update_requested;
    int32_t yearly_births;
    int32_t yearly_deaths;
    int32_t lost_removal;
    int32_t lost_homeless;
    int32_t lost_troop_request;
    int32_t last_change;
    int32_t total_all_years;
    int32_t total_years;
    int32_t average_per_year;
    int32_t highest_ever;
    int32_t total_capacity;
    int32_t room_in_houses;

    int32_t people_in_huts;
    int32_t people_in_shanties;
    int32_t people_in_residences;
    int32_t people_in_manors;
    int32_t percentage_plebs;

    int32_t last_used_house_add;
    int32_t last_used_house_remove;
    int32_t graph_order;

    void recalculate();
    void yearly_recalculate();
    void yearly_update();
    int average_age();
    void add(int num_people);
    void remove(int num_people);
    void add_homeless(int num_people);
    void remove_homeless(int num_people);
    void remove_home_removed(int num_people);
    void remove_for_troop_request(int num_people);
    void record_monthly();
    void update_day();
    int percentage_in_shanties();
    int percentage_in_manors();

    int add_to_houses(int num_people);
    int remove_from_houses(int num_people);
    int create_immigrants(int num_people);
    void update_room();
    int create_emigrants(int num_people);
    void reached_milestone(bool force);
    void evict_overcrowded();
    void update_migration();
    void calculate_working_people();

    void yearly_advance_ages_and_calculate_deaths();
};

int city_population_last_used_house_add();
void city_population_set_last_used_house_add(int building_id);

int city_population_last_used_house_remove();
void city_population_set_last_used_house_remove(int building_id);

void city_population_clear_capacity();
void city_population_add_capacity(int people_in_house, int max_people);

int city_population_people_of_working_age();

void city_population_calculate_educational_age();

int city_population_monthly_count();

int city_population_at_month(int max_months, int month);

int city_population_at_age(int age);

int city_population_at_level(int house_level);

void city_population_request_yearly_update();

void city_population_check_consistency();

int city_population_graph_order();

void city_population_set_graph_order(int order);

int city_population_open_housing_capacity();

int calculate_total_housing_buildings();

int city_population_open_housing_capacity();

int city_population_total_housing_capacity();

int* calculate_number_of_each_housing_type();

int* calculate_houses_demanding_goods(int* housing_type_counts);

int city_population_yearly_deaths();

int city_population_yearly_births();

int city_population_percent_in_workforce();