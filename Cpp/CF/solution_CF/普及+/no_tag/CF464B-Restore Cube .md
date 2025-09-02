# Restore Cube 

## 题目描述

Peter had a cube with non-zero length of a side. He put the cube into three-dimensional space in such a way that its vertices lay at integer points (it is possible that the cube's sides are not parallel to the coordinate axes). Then he took a piece of paper and wrote down eight lines, each containing three integers — coordinates of cube's vertex (a single line contains coordinates of a single vertex, each vertex is written exactly once), put the paper on the table and left. While Peter was away, his little brother Nick decided to play with the numbers on the paper. In one operation Nick could swap some numbers inside a single line (Nick didn't swap numbers from distinct lines). Nick could have performed any number of such operations.

When Peter returned and found out about Nick's mischief, he started recollecting the original coordinates. Help Peter restore the original position of the points or else state that this is impossible and the numbers were initially recorded incorrectly.

## 样例 #1

### 输入

```
0 0 0
0 0 1
0 0 1
0 0 1
0 1 1
0 1 1
0 1 1
1 1 1
```

### 输出

```
YES
0 0 0
0 0 1
0 1 0
1 0 0
0 1 1
1 0 1
1 1 0
1 1 1
```

## 样例 #2

### 输入

```
0 0 0
0 0 0
0 0 0
0 0 0
1 1 1
1 1 1
1 1 1
1 1 1
```

### 输出

```
NO
```

# 题解

## 作者：灵茶山艾府 (赞：0)

固定其中一个点，枚举其余 $7$ 个点的 $6$ 种排列，计算量 $6^7=279936$。

对于一个立方体，其顶点距离恰好有三种（$l,l\sqrt2,l\sqrt3$），且每种个数不会超过 $12$，可以利用该性质进行判断和剪枝。

AC 代码：（Golang）

```go
package main

import . "fmt"

func dis(p, q [3]int64) int64 {
	return (p[0]-q[0])*(p[0]-q[0]) + (p[1]-q[1])*(p[1]-q[1]) + (p[2]-q[2])*(p[2]-q[2])
}

func main() {
	points := make([][3]int64, 8)
	for i := range points {
		Scan(&points[i][0], &points[i][1], &points[i][2])
	}
	var f func(int, map[int64]int8) bool
	f = func(i int, cntD map[int64]int8) bool {
		if i == 8 {
			return len(cntD) == 3
		}
		p := points[i]
	outer:
		for _, perm := range [][3]int{{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}} {
			cd := map[int64]int8{}
			for d, c := range cntD {
				cd[d] = c
			}
			points[i] = [3]int64{p[perm[0]], p[perm[1]], p[perm[2]]}
			for j := 0; j < i; j++ {
				d := dis(points[i], points[j])
				// 剪枝：点的距离不会超过三种且每种个数不会超过 12
				if cd[d]++; len(cd) > 3 || cd[d] > 12 {
					continue outer
				}
			}
			if f(i+1, cd) {
				return true
			}
		}
		return false
	}
	if f(1, map[int64]int8{}) {
		Println("YES")
		for _, p := range points {
			Println(p[0], p[1], p[2])
		}
	} else {
		Print("NO")
	}
}
```

---

