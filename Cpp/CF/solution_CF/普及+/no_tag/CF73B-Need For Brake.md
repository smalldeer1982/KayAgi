# Need For Brake

## 题目描述

Vasya plays the Need For Brake. He plays because he was presented with a new computer wheel for birthday! Now he is sure that he will win the first place in the championship in his favourite racing computer game!

 $ n $ racers take part in the championship, which consists of a number of races. After each race racers are arranged from place first to $ n $ -th (no two racers share the same place) and first $ m $ places are awarded. Racer gains $ b_{i} $ points for $ i $ -th awarded place, which are added to total points, obtained by him for previous races. It is known that current summary score of racer $ i $ is $ a_{i} $ points. In the final standings of championship all the racers will be sorted in descending order of points. Racers with an equal amount of points are sorted by increasing of the name in lexicographical order.

Unfortunately, the championship has come to an end, and there is only one race left. Vasya decided to find out what the highest and lowest place he can take up as a result of the championship.

## 样例 #1

### 输入

```
3
teama 10
teamb 20
teamc 40
2
10 20
teama
```

### 输出

```
2 3```

## 样例 #2

### 输入

```
2
teama 10
teamb 10
2
10 10
teamb
```

### 输出

```
2 2```

