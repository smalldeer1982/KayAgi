# 题目信息

# New Year and the Treasure Geolocation

## 题目描述

Bob is a pirate looking for the greatest treasure the world has ever seen. The treasure is located at the point $ T $ , which coordinates to be found out.

Bob travelled around the world and collected clues of the treasure location at $ n $ obelisks. These clues were in an ancient language, and he has only decrypted them at home. Since he does not know which clue belongs to which obelisk, finding the treasure might pose a challenge. Can you help him?

As everyone knows, the world is a two-dimensional plane. The $ i $ -th obelisk is at integer coordinates $ (x_i, y_i) $ . The $ j $ -th clue consists of $ 2 $ integers $ (a_j, b_j) $ and belongs to the obelisk $ p_j $ , where $ p $ is some (unknown) permutation on $ n $ elements. It means that the treasure is located at $ T=(x_{p_j} + a_j, y_{p_j} + b_j) $ . This point $ T $ is the same for all clues.

In other words, each clue belongs to exactly one of the obelisks, and each obelisk has exactly one clue that belongs to it. A clue represents the vector from the obelisk to the treasure. The clues must be distributed among the obelisks in such a way that they all point to the same position of the treasure.

Your task is to find the coordinates of the treasure. If there are multiple solutions, you may print any of them.

Note that you don't need to find the permutation. Permutations are used only in order to explain the problem.

## 说明/提示

As $ n = 2 $ , we can consider all permutations on two elements.

If $ p = [1, 2] $ , then the obelisk $ (2, 5) $ holds the clue $ (7, -2) $ , which means that the treasure is hidden at $ (9, 3) $ . The second obelisk $ (-6, 4) $ would give the clue $ (-1,-3) $ and the treasure at $ (-7, 1) $ . However, both obelisks must give the same location, hence this is clearly not the correct permutation.

If the hidden permutation is $ [2, 1] $ , then the first clue belongs to the second obelisk and the second clue belongs to the first obelisk. Hence $ (-6, 4) + (7, -2) = (2,5) + (-1,-3) = (1, 2) $ , so $ T = (1,2) $ is the location of the treasure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1091B/f03c880711f7b9805001588cb705f046f5d5dbf6.png)In the second sample, the hidden permutation is $ [2, 3, 4, 1] $ .

## 样例 #1

### 输入

```
2
2 5
-6 4
7 -2
-1 -3
```

### 输出

```
1 2
```

## 样例 #2

### 输入

```
4
2 2
8 2
-7 0
-2 6
1 -14
16 -12
11 -18
7 -14
```

### 输出

```
9 -12
```

# AI分析结果

### 题目内容重写

**题目描述**

Bob 是一名海盗，正在寻找世界上最大的宝藏。宝藏位于点 $T$，其坐标需要被找到。

Bob 环游世界，在 $n$ 个方尖碑处收集了关于宝藏位置的线索。这些线索是用一种古老的语言书写的，他只能在家解密。由于他不知道哪个线索属于哪个方尖碑，找到宝藏可能是一个挑战。你能帮助他吗？

众所周知，世界是一个二维平面。第 $i$ 个方尖碑位于整数坐标 $(x_i, y_i)$。第 $j$ 个线索由两个整数 $(a_j, b_j)$ 组成，属于方尖碑 $p_j$，其中 $p$ 是 $n$ 个元素的某种（未知）排列。这意味着宝藏位于 $T=(x_{p_j} + a_j, y_{p_j} + b_j)$。这个点 $T$ 对于所有线索都是相同的。

换句话说，每个线索恰好属于一个方尖碑，每个方尖碑恰好有一个线索。线索表示从方尖碑到宝藏的向量。线索必须以这样的方式分布在方尖碑之间，使得它们都指向宝藏的相同位置。

你的任务是找到宝藏的坐标。如果有多个解，你可以输出其中任何一个。

注意，你不需要找到排列。排列仅用于解释问题。

**说明/提示**

当 $n = 2$ 时，我们可以考虑所有两个元素的排列。

如果 $p = [1, 2]$，那么方尖碑 $(2, 5)$ 持有线索 $(7, -2)$，这意味着宝藏位于 $(9, 3)$。第二个方尖碑 $(-6, 4)$ 将给出线索 $(-1,-3)$ 和宝藏 $(-7, 1)$。然而，两个方尖碑必须给出相同的位置，因此这显然不是正确的排列。

如果隐藏的排列是 $[2, 1]$，那么第一个线索属于第二个方尖碑，第二个线索属于第一个方尖碑。因此 $(-6, 4) + (7, -2) = (2,5) + (-1,-3) = (1, 2)$，所以 $T = (1,2)$ 是宝藏的位置。

**样例 #1**

输入：
```
2
2 5
-6 4
7 -2
-1 -3
```

输出：
```
1 2
```

**样例 #2**

输入：
```
4
2 2
8 2
-7 0
-2 6
1 -14
16 -12
11 -18
7 -14
```

输出：
```
9 -12
```

### 算法分类
数学

### 题解分析与结论

#### 题解1：installb
**星级：5**
**关键亮点：**
- 通过将所有坐标相加并除以 $n$ 来直接计算宝藏的位置，避免了复杂的排列组合。
- 强调了使用 `long long` 类型的重要性，防止溢出。
- 代码简洁，思路清晰，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
LL x,y,X = 0,Y = 0;
int main(){
	register LL n;
	cin >> n;
	for(int i = 1;i <= n + n;i ++){
		cin >> x >> y;
		X += x; 
		Y += y;
	}
	cout << X / n << " " << Y / n << endl;
	return 0;
}
```

#### 题解2：woshishei
**星级：4**
**关键亮点：**
- 通过排序和配对的方式，将方尖碑和线索的坐标进行匹配，时间复杂度为 $O(n \log n)$。
- 提供了多种解法，包括枚举排列和排序配对，展示了不同的思路。

**核心代码：**
```cpp
sort(a+1,a+n+1,cmp1);//升序
sort(b+1,b+n+1,cmp2);//降序
printf("%d %d",a[1].x+b[1].x,a[1].y+b[1].y);
```

#### 题解3：King_duck
**星级：4**
**关键亮点：**
- 直接通过求和并除以 $n$ 来计算宝藏的位置，思路简单直接。
- 代码简洁，易于理解。

**核心代码：**
```cpp
long long n,x,y,sx,sy;
int main()
{
	cin>>n;
	for(long long i=1;i<=2*n;i++)
	{
		cin>>x>>y;
		sx+=x;
		sy+=y;
	} 
	cout<<sx/n<<" "<<sy/n<<endl;
	return 0;
}
```

### 最优关键思路或技巧
- **求和法**：通过将所有坐标相加并除以 $n$ 来直接计算宝藏的位置，避免了复杂的排列组合，时间复杂度为 $O(n)$，是最优解法。
- **数据类型选择**：在处理大范围数据时，使用 `long long` 类型防止溢出。

### 可拓展之处
- 类似的问题可以通过求和或其他数学方法来简化计算，避免复杂的排列组合。
- 在处理坐标相关的问题时，可以考虑使用排序、配对等方法来简化问题。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

### 个人心得摘录
- **installb**：强调了使用 `long long` 类型的重要性，防止溢出。
- **woshishei**：在比赛中竟然想了20分钟，展示了不同解法的思考过程。
- **King_duck**：直接通过求和并除以 $n$ 来计算宝藏的位置，思路简单直接。

---
处理用时：42.81秒