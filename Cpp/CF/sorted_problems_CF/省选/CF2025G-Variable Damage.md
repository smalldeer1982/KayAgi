---
title: "Variable Damage"
layout: "post"
diff: 省选/NOI-
pid: CF2025G
tag: ['贪心', '分块']
---

# Variable Damage

## 题目描述

Monocarp is gathering an army to fight a dragon in a videogame.

The army consists of two parts: the heroes and the defensive artifacts. Each hero has one parameter — his health. Each defensive artifact also has one parameter — its durability.

Before the battle begins, Monocarp distributes artifacts to the heroes so that each hero receives at most one artifact.

The battle consists of rounds that proceed as follows:

- first, the dragon deals damage equal to $ \frac{1}{a + b} $ (a real number without rounding) to each hero, where $ a $ is the number of heroes alive and $ b $ is the number of active artifacts;
- after that, all heroes with health $ 0 $ or less die;
- finally, some artifacts are deactivated. An artifact with durability $ x $ is deactivated when one of the following occurs: the hero holding the artifact either dies or receives $ x $ total damage (from the start of the battle). If an artifact is not held by any hero, it is inactive from the beginning of the battle.

The battle ends when there are no heroes left alive.

Initially, the army is empty. There are $ q $ queries: add a hero with health $ x $ or an artifact with durability $ y $ to the army. After each query, determine the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 输入格式

The first line contains one integer $ q $ ( $ 1 \le q \le 3 \cdot 10^5 $ ) — the number of queries.

In the $ i $ -th of the following $ q $ lines, there are two integers $ t_i $ and $ v_i $ ( $ t_i \in \{1, 2\} $ ; $ 1 \le v_i \le 10^9 $ ) — the type of the query and the value of the query parameter. If the type is $ 1 $ , a hero with health $ v_i $ is added. If the type is $ 2 $ , an artifact with durability $ v_i $ is added.

## 输出格式

Print $ q $ integers. After each query, output the maximum number of rounds that Monocarp can survive if he distributes the artifacts optimally.

## 说明/提示

Let's consider the first example.

- An artifact with durability $ 5 $ is added. Since there are no heroes yet, the battle ends immediately.
- A hero with health $ 4 $ is added. Monocarp can give him an artifact with durability $ 5 $ . First, there are rounds in which the hero takes $ \frac{1}{1 + 1} = \frac{1}{2} $ damage. After $ 8 $ such rounds, a total of $ 4 $ damage will have been dealt, and the hero will die, while the artifact will deactivate. There are no more heroes alive, so the battle ends after $ 8 $ rounds.
- A hero with health $ 10 $ is added. Now let the artifact with durability $ 5 $ be with this hero. Then, in the first $ 12 $ rounds, the heroes will take $ 12 \cdot \frac{1}{2 + 1} = 4 $ damage, and the first hero will die. The second hero has $ 6 $ health left, and the artifact has $ 1 $ durability. Now the damage is $ \frac{1}{2} $ , so after another $ 2 $ rounds, the artifact will deactivate. The second hero has $ 5 $ health left. After another $ 5 $ rounds, the second hero will die. Therefore, the answer is $ 12 + 2 + 5 = 19 $ .

## 样例 #1

### 输入

```
3
2 5
1 4
1 10
```

### 输出

```
0
8
19
```

## 样例 #2

### 输入

```
10
1 9
1 6
2 4
1 8
1 3
2 10
1 3
1 6
1 10
2 6
```

### 输出

```
9
15
19
27
30
39
42
48
59
65
```

