log_info("akhenaten: ui advisor military started")

advisor_military_window = {
    ui : {
        background   : outer_panel({size:[40, 27]})

        title        : text({pos:[60, 12], text:{group:51, id:0}, font : FONT_LARGE_BLACK_ON_LIGHT })
        advisor_icon : image({pack:PACK_GENERAL, id:128, offset:1, pos:[10, 10] })

        h1           : text({text:{group:51, id:1}, pos:[374, 43], font:FONT_SMALL_PLAIN})
        h2           : text({text:{group:51, id:2}, pos:[374, 58], font:FONT_SMALL_PLAIN})
        h3           : text({text:{group:51, id:3}, pos:[454, 43], font:FONT_SMALL_PLAIN})
        h4           : text({text:{group:51, id:4}, pos:[454, 58], font:FONT_SMALL_PLAIN})
        h5           : text({text:{group:51, id:5}, pos:[534, 43], font:FONT_SMALL_PLAIN})
        h6           : text({text:{group:51, id:6}, pos:[534, 58], font:FONT_SMALL_PLAIN})
        h7           : text({text:{group:138, id:36}, pos:[274, 58], font:FONT_SMALL_PLAIN})

        forts_area   : text({
            pos:[60, 348]
            ui : {
                imgb1       : image({group:PACK_GENERAL, id:158, pos:[0, 10]})
                enemy_text  : text({pos:[20, 10], font:FONT_NORMAL_BLACK_ON_LIGHT})

                imgb2       : image({group:PACK_GENERAL, id:158, pos:[0, 30]})
                distant_text: text({pos:[20, 30], font:FONT_NORMAL_BLACK_ON_LIGHT})

                forts_text  : text({pos:[80, 348], font:FONT_NORMAL_BLACK_ON_LIGHT})
            }
        }),

        inner_panel  : inner_panel({pos:[16, 70], size:[36, 17]})

        //
        no_legions   : text({text:{group:51, id:16}, pos:[64, 200], wrap:496, font:FONT_NORMAL_BLACK_ON_DARK, multiline:true})
    }
}