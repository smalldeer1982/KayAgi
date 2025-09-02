---
title: "Air Reform"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF1648E
tag: ['生成树']
---

# Air Reform

## 题目描述

Berland is a large country with developed airlines. In total, there are $ n $ cities in the country that are historically served by the Berlaflot airline. The airline operates bi-directional flights between $ m $ pairs of cities, $ i $ -th of them connects cities with numbers $ a_i $ and $ b_i $ and has a price $ c_i $ for a flight in both directions.

It is known that Berlaflot flights can be used to get from any city to any other (possibly with transfers), and the cost of any route that consists of several consequent flights is equal to the cost of the most expensive of them. More formally, the cost of the route from a city $ t_1 $ to a city $ t_k $ with $ (k-2) $ transfers using cities $ t_2,\ t_3,\ t_4,\ \ldots,\ t_{k - 1} $ is equal to the maximum cost of flights from $ t_1 $ to $ t_2 $ , from $ t_2 $ to $ t_3 $ , from $ t_3 $ to $ t_4 $ and so on until the flight from $ t_{k - 1} $ to $ t_k $ . Of course, all these flights must be operated by Berlaflot.

A new airline, S8 Airlines, has recently started operating in Berland. This airline provides bi-directional flights between all pairs of cities that are not connected by Berlaflot direct flights. Thus, between each pair of cities there is a flight of either Berlaflot or S8 Airlines.

The cost of S8 Airlines flights is calculated as follows: for each pair of cities $ x $ and $ y $ that is connected by a S8 Airlines flight, the cost of this flight is equal to the minimum cost of the route between the cities $ x $ and $ y $ at Berlaflot according to the pricing described earlier.

It is known that with the help of S8 Airlines flights you can get from any city to any other with possible transfers, and, similarly to Berlaflot, the cost of a route between any two cities that consists of several S8 Airlines flights is equal to the cost of the most expensive flight.

Due to the increased competition with S8 Airlines, Berlaflot decided to introduce an air reform and change the costs of its flights. Namely, for the $ i $ -th of its flight between the cities $ a_i $ and $ b_i $ , Berlaflot wants to make the cost of this flight equal to the minimum cost of the route between the cities $ a_i $ and $ b_i $ at S8 Airlines. Help Berlaflot managers calculate new flight costs.

## 输入格式

Each test consists of multiple test cases. The first line contains one integer $ t $ ( $ 1 \le t \le 10\,000 $ ) — the amount of test cases.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 4 \le n \le 200\,000 $ , $ n - 1 \le m \le 200\,000 $ , $ m \le \frac{(n - 1) (n - 2)}{2} $ ) — the amount of cities in Berland and the amount of Berlaflot flights.

The next $ m $ lines contain the description of Berlaflot flights. The $ i $ -th line contains three integers $ a_i $ , $ b_i $ and $ c_i $ ( $ 1 \le a_i, b_i \le n $ , $ 1 \le c_i \le 10^9 $ ) — the numbers of cities that are connected with $ i $ -th Berlaflot flight and the price of $ i $ -th Berlaflot flight.

It is guaranteed that no flight connects a city with itself, no two flights connect the same pair of cities. It is guaranteed that by using Berlaflot flights it is possible to get from any city to any other and by using S8 Airlines flights it is possible to get from any city to any other.

Let $ N $ be the sum of $ n $ over all test cases and $ M $ be the sum of $ m $ over all test cases. It is guaranteed that $ N, M \le 200\,000 $ .

## 输出格式

For each test case you should print $ m $ integers in a single line, $ i $ -th of them should be the price of $ i $ -th Berlaflot flight after the air reform.

## 说明/提示

In the first test case S8 Airlines will provide flights between these pairs of cities: $ (1, 3) $ , $ (1, 4) $ and $ (2, 4) $ .

The cost of a flight between cities $ 1 $ and $ 3 $ will be equal to $ 2 $ , since the minimum cost of the Berlaflot route is $ 2 $ — the route consists of a flight between cities $ 1 $ and $ 2 $ costing $ 1 $ and a flight between cities $ 2 $ and $ 3 $ costing $ 2 $ , the maximum cost is $ 2 $ .

The cost of a flight between cities $ 1 $ and $ 4 $ will be $ 3 $ , since the minimum cost of the Berlaflot route is $ 3 $ — the route consists of a flight between cities $ 1 $ and $ 2 $ costing $ 1 $ , a flight between cities $ 2 $ and $ 3 $ costing $ 2 $ and a flight between cities $ 3 $ and $ 4 $ costing $ 3 $ , the maximum cost is $ 3 $ .

The cost of a flight between cities $ 2 $ and $ 4 $ will be $ 3 $ , since the minimum cost of the Berlaflot route is $ 3 $ — the route consists of a flight between cities $ 2 $ and $ 3 $ costing $ 2 $ and a flight between cities $ 3 $ and $ 4 $ costing $ 3 $ , the maximum cost is $ 3 $ .

After the air reform, the cost of the Berlaflot flight between cities $ 1 $ and $ 2 $ will be $ 3 $ , since the minimum cost of the S8 Airlines route between these cities is $ 3 $ — the route consists of a flight between cities $ 1 $ and $ 4 $ costing $ 3 $ and a flight between cities $ 2 $ and $ 4 $ costing $ 3 $ , the maximum cost is $ 3 $ .

The cost of the Berlaflot flight between cities $ 2 $ and $ 3 $ will be $ 3 $ , since the minimum cost of the S8 Airlines route between these cities is $ 3 $ — the route consists of a flight between cities $ 2 $ and $ 4 $ costing $ 3 $ , a flight between cities $ 1 $ and $ 4 $ costing $ 3 $ and a flight between $ 1 $ and $ 3 $ costing $ 2 $ , the maximum cost is $ 3 $ .

The cost of the Berlaflot flight between cities $ 3 $ and $ 4 $ will be $ 3 $ , since the minimum cost of the S8 Airlines route between these cities is $ 3 $ — the route consists of a flight between cities $ 1 $ and $ 3 $ costing $ 2 $ and a flight between cities $ 1 $ and $ 4 $ costing $ 3 $ , the maximum cost is $ 3 $ .

 In the second test case S8 Airlines will have the following flights: between cities $ 1 $ and $ 4 $ costing $ 1 $ , between cities $ 2 $ and $ 3 $ costing $ 1 $ , between cities $ 2 $ and $ 5 $ costing $ 2 $ , between cities $ 3 $ and $ 4 $ costing $ 1 $ and between cities $ 3 $ and $ 5 $ costing $ 2 $ .

## 样例 #1

### 输入

```
3
4 3
1 2 1
2 3 2
4 3 3
5 5
1 2 1
1 3 1
2 4 1
4 5 2
5 1 3
6 6
1 2 3
2 3 1
3 6 5
3 4 2
4 5 4
2 4 2
```

### 输出

```
3 3 3 
1 1 1 2 2 
4 4 5 3 4 4
```



---

---
title: "Railway Construction"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF2041N
tag: ['生成树']
---

# Railway Construction

## 题目描述

The country of Truckski is located in a rugged, mountainous region, and the geological condition has engendered a wide range of issues. The challenging terrain separates the different states in the country, resulting in an extremely inconvenient inter-state commute and more crucially a lack of central governmental control. Adding on top of that is a rampant crime rate that increases annually, and this severely disrupts the everyday lives of innocent citizens.

A recent protest finally shed light on the situation, as the newly elected president has announced an ambitious project to resolve these issues. Her plan consists of two major components. The first is the construction of high-speed railways between the states to facilitate better connections and unity across the country. Since the states are mostly running independently from each other, to construct a railway between states $ u $ and $ v $ , the government has to pay a fee of $ a_u + a_v $ dollars, with $ a_u $ dollars given to state $ u $ and $ a_v $ dollars given to state $ v $ . The railway operates bidirectionally, meaning that once it is built, people from state $ u $ can now travel to state $ v $ and vice versa. A railway can be built between almost any pair of states, except for $ m $ particular pairs for which the terrain dividing them is so treacherous that the construction of a direct railroad between the two states becomes impossible.

The second component of the project is to build a centralized prison that manages all criminals across the country. Given the large number of estimated prisoners, the president decided to pick one of the states to build the central prison and sever the connection from the state to the rest of the country.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2041N/b8bb40d48431245ffbc89adca1f7afc2de2f208d.png) An illustration for the sample input 1. (a) The costs of building direct railways between the states. (b) Consider building the central prison in State #3. All direct railroads that do not involve State #3 have to be built, with a total cost of $ 3+3+2=8 $ dollars.Given the above, the president would like to search for the minimum cost plan to construct railroads between the states so that:

- the state with the central prison should not have any railway connecting it to any other states, and
- all the other states should be connected, i.e., people should be able to travel from one such state to another, possibly by taking more than one train.

You are working for the team in charge of the overall planning of the construction. The meeting with the president is happening in just a few hours, at which time you will have to brief her on the cost of different construction plans. Please calculate, for each state $ u $ , the minimum cost plan to construct railroads between states meeting the above conditions when $ u $ is where the central prison is built.

## 输入格式

The first line of the input contains two integers $ n $ and $ m $ , the number of states in Truckski and the number of pairs for which railroad construction is not feasible. The next line contains $ n $ integers $ a_1, \ldots, a_n $ , the construction fee the government needs to pay to the $ i $ -th state. Then, $ m $ lines follow. The $ i $ -th line contains two integers $ u_i $ and $ v_i $ meaning that it is impossible to build a (direct) railway between states $ u_i $ and $ v_i $ .

- $ 2\leq n\leq 10^5 $
- $ 0\leq m\leq 10^5 $
- $ 1\leq a_i\leq 10^9 $
- $ 1\leq u_i<v_i\leq n $
- For all $ i\neq j, (u_i, v_i)\neq (u_j, v_j) $ .

## 输出格式

Output $ n $ integers in one line. The $ i $ -th integer is the minimum construction cost when the $ i $ -th state is where the prison is built. If it is impossible to find a feasible railroad construction, output -1 instead.

## 样例 #1

### 输入

```
5 3
1 2 1 1 1
1 4
1 5
2 5
```

### 输出

```
7 6 8 7 7
```

## 样例 #2

### 输入

```
3 2
1 2 3
1 2
2 3
```

### 输出

```
-1 4 -1
```



---

---
title: "Tourist Guide"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF589H
tag: ['搜索', '生成树', '最近公共祖先 LCA']
---

# Tourist Guide

## 题目描述

It is not that easy to create a tourist guide as one might expect. A good tourist guide should properly distribute flow of tourists across the country and maximize the revenue stream from the tourism. This is why there is a number of conditions to be met before a guide may be declared as an official tourist guide and approved by Ministry of Tourism.

Ministry of Tourism has created a list of $ k $ remarkable cities out of $ n $ cities in the country. Basically, it means that in order to conform to strict regulations and to be approved by the ministry a tourist guide should be represented as a set of routes between remarkable cities so that the following conditions are met:

- the first and the last city of every route are distinct remarkable cities,
- each remarkable city can be an endpoint of at most one route,
- there is no pair of routes which share a road.

Please note that a route may pass through a remarkable city. Revenue stream from the tourism highly depends on a number of routes included in a tourist guide so the task is to find out a set of routes conforming the rules of a tourist guide with a maximum number of routes included.

## 输入格式

The first line contains three integer numbers $ n,m,k $ $ (1<=n<=50000,0<=m<=50000,1<=k<=n) $ — the number of cities in the country, the number of roads in the country and the number of remarkable cities correspondingly.

Each of the following $ m $ lines contains two integer numbers $ a_{i} $ and $ b_{i} $ $ (1<=a_{i},b_{i}<=n) $ — meaning that cities $ a_{i} $ and $ b_{i} $ are connected by a bidirectional road. It is guaranteed that $ a_{i} $ and $ b_{i} $ are distinct numbers and there is no more than one road between a pair of cities.

The last line contains $ k $ distinct integer numbers — a list of remarkable cities. All cities are numbered from 1 to $ n $ .

## 输出格式

The first line of the output should contain $ c $ — the number of routes in a tourist guide. The following $ c $ lines should contain one tourist route each. Every route should be printed in a form of " $ t $ $ v_{1} $ $ v_{2} $ ... $ v_{t+1} $ ", where $ t $ is a number of roads in a route and $ v_{1},v_{2},...,v_{t+1} $ — cities listed in the order they are visited on the route.

If there are multiple answers print any of them.

## 样例 #1

### 输入

```
6 4 4
1 2
2 3
4 5
5 6
1 3 4 6

```

### 输出

```
2
2 1 2 3
2 4 5 6

```

## 样例 #2

### 输入

```
4 3 4
1 2
1 3
1 4
1 2 3 4

```

### 输出

```
2
1 1 2
2 3 1 4

```



---

