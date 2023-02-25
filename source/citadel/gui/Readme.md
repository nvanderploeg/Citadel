#  n0 GUI  Readme / Technical Doc


## GUI layouts
Justification: 
Parent Children Relationship
The goal of the n0 system is to keep the structure of the parent child relationship 1 directional. However this poses many problem when trying to have UI object justify themselves relative to their parents. How can a child button Anchor to the left or right of the parent Panel.
To facilitate this I am thinking the Parent must be a decision maker in cases of any sort of auto layout.
Parents given Children a box to play in, In most cases this will be the render area of the parent, but it could be a sub section or anything else.
This is denoted by the worldZone area, giving pixels for the child to operate in. Then if the child wishes to Anchor itself to a side, or make itself a relative size, or whatever, it can do that in that worldZone area.

# GUI Structure

The N0 Gui system is designed to be an integrated but independant systems to work within the game engine.
There is not a Single GUI for a given application but many GUI Environments, each n0 Scene has it's own Environement by default but any additonal Environments can be added and run at any time.

## Core
A gui Environment is the base point for any GUI systems to run, everything inside an enviorment renders from TopLeft of the origin, based on the size of the Environment.
The GUIFactory is a helper class to allow environments to be dynamically created from json files.
GUIObject is the base object in the GUI system from which all other objects should inherit. It makes up the basic structure used in the GUI tree.
GUIRenderObjects are a renderable component to be used by GUI widgets.


## Materials / RenderObjects
A GUI Material is a Set of render parameters to be used in a render object. a Material might have a texture, Texture Coords, a shader, Blend mode, etc.
GUI Render Objects are Drawable Components to match the functionality provided by widgets. Most widgets will have render components by default, such as a panel having a background render component, or a button having render objects for it's various states.(mouse over)

## Widgets
Widgets are the building blocks of the GUI system, some are composite of other widgets, for example, a Slider is two panels (background and bar) and two buttons.

### Buttons

### Panel

### Sliders

### Text

### Toggle

### ScrollView

### Carosel

### Checkbox

### Masks


# GUI Scripting
All scripting in the GUI system takes place via JSON config files., These configs could be generated manually, or through a GUI tool or automation.
Scripts can either be directly part of a GUI json file, or references as an addon file within the GUI system.

    ex.
    { ...
    "type":"GUIPanel",
    "script" : {} || "buttonScript.gui"
    }

## Triggers
Triggers are a idea of things UI Objects might react too, Such as being Presented, a Button being clicked, being closed, dragged, or resized, or mouseover events.
Triggers can also work off of general events being emitted through the system.

## Actions
Actions are things the GUI system understand how to do, for example, opening or closing a panel, Clicking a button, Loading or unloading an enviroment, and emiiting game or UI events.
Refreshing Layout, 

Actions can target a specific GUIObject by id, or using _self the host object. If no target is set, the environment is targeted instead.

Actions can contain a Payload object, that will be interpreted by the object that responds to the action, for example loading a GUI has no target, so it targets the enviroment.

## example
{ 
    "triggers" : [
    {
        "type" : "click",
        "actions" : [ 
            {
                "type" : "loadGUI",
                "payload" : {
                    "file" : "menu2.gui"
                }
            },
            {
                "type" : "close"
                "target" : "_self"
            }
        ],
    },
    { 
        "type" : "resize",
        "actions" : [ 
            {
                "type" : "layout",
                "target" : "_self"
            }
        ]
    }
    ]
}
