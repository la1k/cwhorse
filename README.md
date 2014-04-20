cwhorse
=======

CW decoding program inspired by cwskimmer (http://www.dxatlas.com/cwskimmer/).
Will decode CW in parallel on multiple streams, and display decoded text or
extracted callsigns side-by-wide with a waterfall display.  

Decoding will be done by a separate library, likely based on morse-wip
(https://github.com/ag1le/morse-wip), which is based on FORTRAN code found in
"Optimal Bayesian estimation of the state of a probabilistically mapped
memory-conditional Markov process with application to manual morse decoding" by
E. L. Bell, 1977 (PhD thesis).

The name CW HORSE should induce vivid images of horses sniffing the
radio-frequent ground for morse signals.

                        ..,,,,_          ____
                       /(\())) "-.____.-"    `-.-,
                     /''))))'                  \)))
                    %()(()                       ((((
                   (()(/                          |))))
                  /~()) |                          (((((
                 )()(/  /\                  |       ))))))
                /)(*   / `|    |           ,\     /((((((
             , )\)))  /   |   / `-.______.<  \   |  )))))
          _,,)\.~,)  /    |   |  /         `. \  \  ((((
          (()`  ``  /     |  / \ |           `.\  | (((
           |     \ /      \  | | |             )| |  ))
           |6`   |/        | | | |            / | |  '
           |    .'         | | /_(           /_(/ /
           |   |           /_(/__]           \_/_(
           \, _)          /__]                /__]
    --... ...--  -.. .  .-.. .- .---- -.-  .-.. -. .---- -.-
