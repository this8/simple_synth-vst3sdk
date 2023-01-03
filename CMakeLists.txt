cmake_minimum_required(VERSION 3.14.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.13 CACHE STRING "")

set(vst3sdk_SOURCE_DIR "/Users/thisura/Xcode/vst3sdk")
if(NOT vst3sdk_SOURCE_DIR)
    message(FATAL_ERROR "Path to VST3 SDK is empty!")
endif()

project(Musynth
    # This is your plug-in version number. Change it here only.
    # Version number symbols usable in C++ can be found in
    # source/version.h and ${PROJECT_BINARY_DIR}/projectversion.h.
    VERSION 1.0.0.0 
    DESCRIPTION "Musynth VST 3 Plug-in"
)

set(SMTG_VSTGUI_ROOT "${vst3sdk_SOURCE_DIR}")

add_subdirectory(${vst3sdk_SOURCE_DIR} ${PROJECT_BINARY_DIR}/vst3sdk)
smtg_enable_vst3_sdk()

smtg_add_vst3plugin(Musynth
    source/version.h
    source/musynthcids.h
    source/musynthprocessor.h
    source/musynthprocessor.cpp
    source/musynthcontroller.h
    source/musynthcontroller.cpp
    source/musynthentry.cpp
)

#- VSTGUI Wanted ----
if(SMTG_ADD_VSTGUI)
    target_sources(Musynth
        PRIVATE
            resource/musyntheditor.uidesc
    )
    target_link_libraries(Musynth
        PRIVATE
            vstgui_support
    )
    smtg_target_add_plugin_resources(Musynth
        RESOURCES
            "resource/musyntheditor.uidesc"
    )
endif(SMTG_ADD_VSTGUI)
# -------------------

smtg_target_add_plugin_snapshots (Musynth
    RESOURCES
        resource/5B309FE32906543592B9A5A39B2C39D6_snapshot.png
        resource/5B309FE32906543592B9A5A39B2C39D6_snapshot_2.0x.png
)

target_link_libraries(Musynth
    PRIVATE
        sdk
)

smtg_target_configure_version_file(Musynth)

if(SMTG_MAC)
    smtg_target_set_bundle(Musynth
        BUNDLE_IDENTIFIER com.musiola.musynth
        COMPANY_NAME "Musiola"
    )
    smtg_target_set_debug_executable(Musynth
        "/Applications/VST3PluginTestHost.app"
        "--pluginfolder;$(BUILT_PRODUCTS_DIR)"
    )
elseif(SMTG_WIN)
    target_sources(Musynth PRIVATE 
        resource/win32resource.rc
    )
    if(MSVC)
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Musynth)

        smtg_target_set_debug_executable(Musynth
            "$(ProgramW6432)/Steinberg/VST3PluginTestHost/VST3PluginTestHost.exe"
            "--pluginfolder \"$(OutDir)/\""
        )
    endif()
endif(SMTG_MAC)
