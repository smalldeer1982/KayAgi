---
title: "Cursed Game"
layout: "post"
diff: 省选/NOI-
pid: CF1906C
tag: []
---

# Cursed Game

## 题目描述

You found an antique box in your warehouse and decided to open it. The moment you open the box, it traps you into a cursed game where you are playing against a demon. The game consists of $ 333 $ rounds and you have to win all rounds in order to escape. The demon also gives you $ 999 $ coins that you can use throughout all rounds.

Note that in this problem, denote cell $ (r, c) $ of a grid as the cell in row $ r $ and column $ c $ of the grid.

Before the start of each round, the demon will prepare a secret paper, which can be represented as a grid with $ 3 $ rows and $ 3 $ columns, both numbered from $ 1 $ to $ 3 $ . The demon will secretly put a hole in one or more cells, and you are not aware which cells have a hole in it. Then, the round starts with the demon giving you an odd integer $ N $ ( $ 3 \leq N \leq 33 $ ).

Within each round, you can ask the demon several queries, each costing you one coin. For each query, you are allowed to give the demon your paper, which can be represented as a grid with $ N $ rows and $ N $ columns, both numbered from $ 1 $ to $ N $ . Each cell is coloured either black or white by you.

For each of your query, the demon will calculate a binary result grid with $ N - 2 $ rows and $ N - 2 $ columns, both numbered from $ 1 $ to $ N - 2 $ . The value on cell $ (r, c) $ of the result grid is filled as follows.

- The demon will put the secret paper on top of your paper such that the cell $ (r + i - 1, c + j - 1) $ of your paper aligns with the cell $ (i, j) $ of the secret paper, for $ 1 \leq i, j \leq 3 $ .
- The demon can only see the colour of the cell in your paper if the corresponding cell in the secret paper has a hole in it.
- The value on cell $ (r, c) $ of the result grid is $ 1 $ if there is an odd number of black cells that it can see through the holes, or $ 0 $ otherwise.

You win the round if the result grid consists of only the values $ 1 $ . Otherwise, the demon will give you the result grid as a feedback, and the round continues.

If you have spent all the coins and still did not win all the rounds, then you will be trapped forever. Escape the cursed game!

## 说明/提示

Sample Interaction #1

The following interaction only shows $ 2 $ rounds. The actual interaction stays until you win all $ 333 $ rounds or you run out of coins.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906C/37c84dede82381a4f24254eee6774fc481cfcb99.png)Explanation for the sample interaction #1

For the first round, the following illustration shows how the demon finds the value in cell $ (1, 1) $ of the result grid for the first and second queries. The grey-colored square represents the secret paper, and the circles represent the holes. In the first query, there are $ 4 $ black cells that can be seen through the holes, therefore the value in cell $ (1, 1) $ of the result grid is $ 0 $ . In the second query, there are $ 5 $ black cells that can be seen through the holes, therefore the value in cell $ (1, 1) $ of the result grid is $ 1 $ . As the result grid consists of only 1, the first round ends.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906C/6f97bd68e5e86b9b407597d473edac9794aa20f9.png)For the second round, the following illustration shows how the demon find the value in cell $ (2, 1) $ of the result grid for the first query. Since there are $ 2 $ black cells that can be seen through the holes, the value in cell $ (2, 1) $ is $ 0 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1906C/77cc40cef2907cecd6b6e9d5a9f4895b61aca734.png)

