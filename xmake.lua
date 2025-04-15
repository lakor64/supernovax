add_rules("mode.debug")
set_project("SupernovaX")
set_languages("c++14")

wddm = false
tests = false
sdk_utilities = false
sdk_samples = false

option("enable_wddm")
    set_default(true)
    set_showmenu(true)
    wddm = true

option("enable_snxsdk_internal_tests")
    set_default(true)
    set_showmenu(true)
    tests = true

option("enable_snxsdk_utilities")
    set_default(true)
    set_showmenu(true)
    sdk_utilities = true

option("enable_snxsdk_samples")
    set_default(true)
    set_showmenu(true)
    sdk_samples = true

includes("sdk")
includes("runtime")
