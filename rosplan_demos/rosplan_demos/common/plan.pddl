Number of literals: 11
Constructing lookup tables: [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%] [120%] [130%]
Post filtering unreachable actions:  [10%] [20%] [30%] [40%] [50%] [60%] [70%] [80%] [90%] [100%] [110%] [120%] [130%]
[01;34mNo analytic limits found, not considering limit effects of goal-only operators[00m
All the ground actions in this problem are compression-safe
Initial heuristic = 10.000
b (9.000 | 10.000)b (8.000 | 13.001)b (7.000 | 19.001)b (6.000 | 22.001)b (5.000 | 28.001)b (4.000 | 31.001)b (3.000 | 37.001)b (2.000 | 40.001)b (1.000 | 41.001);;;; Solution Found
; States evaluated: 17
; Cost: 42.001
; Time 0.00
0.000: (initialize wp1)  [10.000]
10.001: (take_hint wp1)  [3.000]
13.001: (goto_waypoint wp1 wp2)  [6.000]
19.001: (take_hint wp2)  [3.000]
22.001: (goto_waypoint wp2 wp3)  [6.000]
28.001: (take_hint wp3)  [3.000]
31.001: (goto_waypoint wp3 wp4)  [6.000]
37.001: (take_hint wp4)  [3.000]
40.001: (check_hp)  [1.000]
41.001: (test_hp)  [1.000]
