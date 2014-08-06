The goal of this document is to outline how I want to arrange my render engine.

Thoughts:

    * Physical Window
        Represents a window on the windowing system. Created through the Window
        class. Has 1+ virtual windows
    * Virtual Window
        Represents a canvas. Must be attached to a physical window to be visible
        (but can be rendered off screen). Most likely implemented using render to
        texture. Each virtual window has 1 world associated with it (the world can
        be set, but there can not be more than 1).
    * World
    * Camera
    * Objects
    * Lights
    * Meshs
    * Assets
    * Textures
    * Renderers
    * Materials