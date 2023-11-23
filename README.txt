v0.0.5

This project is an implementation of the Set data-structure written in C. I plan to rewrite it in
Rust and Go as well. Initially I wanted to do a larger project in C/Rust so I could learn the 
differences between those languages but it turns out C is very hard to write and so I decided
to start with a simple data-structure instead of a whole project.

I have purposefully avoided looking up how to implement a Set in any low level languages so that
I don't cheat. After I finish implementing sets in C, Go, and Rust, I will look up the correct
paradigms for each language. I feel pretty good about my C implementation but Rust and the borrow
checker are going to be quite a bit harder for me to figure out. (Update: The borrow checker 
wasn't relevant in set.rs.)

Because I am implementing the same logic across three languages it will be important to have a
test suite. I haven't quite figured out my methodology yet but I made CLI in c/main.c and my
test suite will probably use that.

Update: As it turns out I finished this project without writing any tests after all. Read more 
about that in docs/POSTMORTEM.txt