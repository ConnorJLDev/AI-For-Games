Student Name: Connor Lariviere

Project Name: "Love Triangle"

What I implemented: I implemented a simulation of a bird mating call ritual between human beings, each one sharing their form of affection to win over the person in the middle. The Lover in the middle takes notice of these actions and will dance/change colors to those they love. The Baron is green and will attempt to give money for affection, the dancer is red and will attempt to dance and sometimes hit a flip for affection, and the Singer is blue and will attempt to sing for affection. If they aren't trying to impress the Lover the Singer will cry and feel sad, the Baron will shrink and feel small, and the Dancer will just sit around cause he needs to store up that energy for dancing. 

Directions (if needed): None.

What I liked about the project and framework: I was able to create something fun and interesting and actually understood what behavior trees did with the GUI rather than other classes/schools that would have made us read textbooks. The framework yet small, was super useful and powerful. 

What I disliked about the project and framework: Not enough documentation on how to use blackboards and having to write into Node.def every single time I wish to create a node.

Any difficulties I experienced while doing the project: I ran into some issues with the blackboard not communicating properly, however I was able to figure it out. Also there was an issue when finding a value to a blackboard before it was set it should just return false, in my opinion instead it would breakpoint. 

Hours spent: 9 hours.

New decorator nodes (names): 
"D_RandomChance": Performed a dice roll to determine if we should enter this leaf or not! 
"D_IsBaronPerforming": Reads a Blackboard that is operated within Baron and checks if he is performing!
"D_IsSingerPerforming": Reads a Blackboard within the Singer and sees if the Singer is Performing!
"D_IsDancerPerforming": Reads a Blackboard within the Dancer and checks to see if the Dancer is Performing!

10 total nodes (names):


"L_SpawnBalls": Spawns money balls to throw out. 
"L_Shrink": Shrinks the agent slightly. If we reach 0 we reset.
"L_RandomChance": Rolls a random chance (isn't used).
"L_PlayBaronSound": Plays sound for Baron's performance.
"L_MoveDownPosition": Moves the agent left 30 spaces.
"L_MoveToUpPosition": Moves the agent right 30 spaces.
"L_BallRemoval": Removes balls overtime and handles movement for balls.
"L_RotDown": Rotates with pitch down for crying cutscene.
"L_RotUp": Rotates with pitch up for crying cutscene.
"L_Cries": Plays audio for Crying. 
"L_Singing": Scales the agent up and down based on a sin function to make it wobble. 

 "L_Dance": Makes the agent spin for a few seconds.
"L_MoveNorth": Moves the agent north 30m. 
"L_MoveSouth": Moves the agent south 30m.
"L_DanceSound": Plays the sound for the dance sequence.
"L_EndWithFlip": Rotates the agent in a flipping motion and moves them up and down, also plays the audio for the flip.

"L_StartBaronPerforming": Writes to the blackboard to mark true for performing.
"L_EndBaronPerforming":Writes to the blackboard to mark false for performing.

"L_LoverInit": Unused previously for initializing blackboards.
"L_LookEast": Makes the agent look East.
"L_LookSouth:Makes the agent look South.
"L_LookWest":Makes the agent look West.
"L_ChangeBlue": Makes the agent Blue.
"L_ChangeRed": Makes the agent Red. 
"L_ChangeGreen":Makes the agent Green.
"L_JumpUpDown.h":Makes the agent Jump up and down.
"L_LookNorth.h": Makes the agent look North. 

4 Behavior trees (names):
Baron - Will perform and spawn balls of money to throw at the lover, when finished he will sit and wait for his turn, and shrink when he's sad.
Dancer - Will perform a dance of spinning and will even flip at the end, when finished he will flop over and be tired and wait till he has energy to perform again.
Lover - Will look at anyone showing their love and affection and will show them they love them through matching their color and dance for them. If there is no one performing she will wait for someone. 
Singer - He is really sad and will often cry, but when he is not crying he will sing to perform and when he is done he will wait for his throat to heal. 

Ball - Just spawns ball and destroys no depth.

Extra credit: N/A? 