# [SWERC 2023] Supporting everyone

## 题目描述

:::align{center}

![](https://espresso.codeforces.com/9b693d641063096ae32c5b06333b6fdf2138d3da.png)

:::

Alice is attending a sport event with many national teams and one thing is important to her: supporting every country.


There are $N$ countries represented and she has two ways to support a country: either have the flag drawn on her or have a pin with the name of the country. Alice has a list containing, for each country, the colours needed to make its flag. A total of $M$ colours that may appear across all flags and, in Alice&#39;s list, each colour is conveniently represented as an integer between $1$ and $M$.


Each crayon and pin cost $1$, but her budget is tight... Can you help her find the minimum she can spend to support everyone?

## 说明/提示

**Sample Explanation 1**

The three first countries could be France, the Netherlands, and the Czech Republic, all represented by
blue (1), white (4), and red (5). The three next countries could be Italy, Hungary, and Bulgaria, with
green (3), white (4) and red (5). The last one could be Germany, with black (2), red (5), and yellow (6).
The minimum cost is 5: we buy four (blue, green, white, and red) crayons and one pin (for Germany).


**Sample Explanation 2**

We can buy two crayons for the colours 7 and 11 and buy two pins for a total cost of 4. All six countries
with flag colours 7 (red) and 11 (white) could be Canada, Indonesia, Japan, Malta, Monaco, and Poland.
The flag of Belize has 12 colours, including red and white, and the fifth country could be Botswana.

## 样例 #1

### 输入

```
7 6
3
1 4 5
3
1 4 5
3
1 4 5
3
3 4 5
3
3 4 5
3
3 4 5
3
2 5 6```

### 输出

```
5```

## 样例 #2

### 输入

```
8 12
2
7 9
12
1 2 3 4 5 6 7 8 9 10 11 12
2
7 9
2
7 9
3
3 4 11
2
7 9
2
7 9
2
7 9```

### 输出

```
4```

