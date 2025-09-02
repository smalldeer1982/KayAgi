# 题目信息

# Vitaliy and Pie

## 题目描述

After a hard day Vitaly got very hungry and he wants to eat his favorite potato pie. But it's not that simple. Vitaly is in the first room of the house with $ n $ room located in a line and numbered starting from one from left to right. You can go from the first room to the second room, from the second room to the third room and so on — you can go from the ( $ n-1 $ )-th room to the $ n $ -th room. Thus, you can go to room $ x $ only from room $ x-1 $ .

The potato pie is located in the $ n $ -th room and Vitaly needs to go there.

Each pair of consecutive rooms has a door between them. In order to go to room $ x $ from room $ x-1 $ , you need to open the door between the rooms with the corresponding key.

In total the house has several types of doors (represented by uppercase Latin letters) and several types of keys (represented by lowercase Latin letters). The key of type $ t $ can open the door of type $ T $ if and only if $ t $ and $ T $ are the same letter, written in different cases. For example, key f can open door F.

Each of the first $ n-1 $ rooms contains exactly one key of some type that Vitaly can use to get to next rooms. Once the door is open with some key, Vitaly won't get the key from the keyhole but he will immediately run into the next room. In other words, each key can open no more than one door.

Vitaly realizes that he may end up in some room without the key that opens the door to the next room. Before the start his run for the potato pie Vitaly can buy any number of keys of any type that is guaranteed to get to room $ n $ .

Given the plan of the house, Vitaly wants to know what is the minimum number of keys he needs to buy to surely get to the room $ n $ , which has a delicious potato pie. Write a program that will help Vitaly find out this number.

## 样例 #1

### 输入

```
3
aAbB
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
aBaCaB
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5
xYyXzZaZ
```

### 输出

```
2
```

# AI分析结果

### 题目翻译
# 维塔利与派

## 题目描述
在辛苦的一天之后，维塔利非常饥饿，他想吃他最喜欢的土豆派。但事情并没有那么简单。维塔利在房子的第一个房间里，房子里有 $n$ 个房间排成一排，从左到右依次编号为 1 到 $n$。你可以从第一个房间走到第二个房间，从第二个房间走到第三个房间，依此类推——你可以从第 $(n - 1)$ 个房间走到第 $n$ 个房间。因此，你只能从第 $x - 1$ 个房间走到第 $x$ 个房间。

土豆派出现在第 $n$ 个房间，维塔利需要走到那里。

每对相邻的房间之间都有一扇门。为了从第 $x - 1$ 个房间走到第 $x$ 个房间，你需要用相应的钥匙打开房间之间的门。

房子里总共有几种类型的门（用大写拉丁字母表示）和几种类型的钥匙（用小写拉丁字母表示）。只有当类型为 $t$ 的钥匙和类型为 $T$ 的门是同一个字母的大小写形式时，钥匙 $t$ 才能打开门 $T$。例如，钥匙 `f` 可以打开门 `F`。

前 $n - 1$ 个房间中的每个房间都恰好有一把某种类型的钥匙，维塔利可以用这些钥匙前往下一个房间。一旦用某把钥匙打开了门，维塔利不会从锁孔中取出钥匙，而是会立即跑进下一个房间。换句话说，每把钥匙最多只能打开一扇门。

维塔利意识到，他可能会在某个房间里没有打开通往下一个房间的门的钥匙。在开始寻找土豆派之前，维塔利可以购买任意数量的任意类型的钥匙，以确保能够到达第 $n$ 个房间。

给定房子的布局，维塔利想知道他至少需要购买多少把钥匙才能确保到达装有美味土豆派的第 $n$ 个房间。编写一个程序来帮助维塔利找出这个数量。

## 样例 #1
### 输入
```
3
aAbB
```
### 输出
```
0
```

## 样例 #2
### 输入
```
4
aBaCaB
```
### 输出
```
3
```

## 样例 #3
### 输入
```
5
xYyXzZaZ
```
### 输出
```
2
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，即钥匙能用就用。具体实现上，均使用了桶（数组或 `map`）来记录每种钥匙的数量。当遇到钥匙时，增加对应钥匙的数量；当遇到门时，检查是否有对应的钥匙，若有则使用（数量减一），若无则购买钥匙（答案加一）。

各题解的区别在于数据的读取方式和使用的数据结构，有的使用 `map` 存储钥匙数量，有的使用固定长度的数组作为桶。

### 所选的题解
- 作者：joy2010WonderMaker，4星。关键亮点：思路清晰，代码简洁，使用固定长度的数组作为桶，直接通过下标操作，效率较高。
- 作者：chufuzhe，4星。关键亮点：明确指出贪心结论并用反证法证明，代码简洁，逻辑清晰。
- 作者：小恐，4星。关键亮点：对题意理解清晰，代码实现简单易懂，通过字符判断处理钥匙和门的情况。

### 重点代码
#### joy2010WonderMaker 的代码
```cpp
#include<cstdio>
int have[26],ans;//have数组就是桶，统计出现次数
char h[200005];//存储字符串
int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",&h);
    for(int i=0;i<2*n-2;i++){
        if(i%2==0)have[h[i]-'a']++;//统计出现次数
        else{
            if(have[h[i]-'A'])have[h[i]-'A']--;//如果有，就将那种钥匙数减1
            else ans++;//如果没有，就将需要的钥匙数加1
        }
    }
    printf("%d",ans);
    return 0;
}
```
核心实现思想：使用 `have` 数组作为桶，通过判断字符的奇偶性区分钥匙和门，对钥匙数量进行增减操作。

#### chufuzhe 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[30]; //桶
int main()
{
	int n, ans = 0;
	cin >> n;
	for(int i = 1; i < n; i++) {
		char a, b;
		cin >> a >> b;
		t[a - 97]++; //a钥匙数量增加1
		if(t[b - 65] > 0) t[b - 65]--; //用了b钥匙
		else ans++; //没有b钥匙，还需要的钥匙数量增加1
	}
	cout << ans << endl;
	return 0;
}
```
核心实现思想：使用 `t` 数组作为桶，每次读取一对钥匙和门的字符，对钥匙数量进行相应操作。

#### 小恐的代码
```cpp
#include<stdio.h>
using namespace std;
char a[200005];
int cnt[27];
int ans;
int main()
{
	int n;
	scanf("%d%s",&n,a);
	for(int i=0;a[i]!='\0';++i)
	{
		if(a[i]>='a'&&a[i]<='z')
			++cnt[a[i]-'a'];
		else
		{
			if(cnt[a[i]-'A'])
				--cnt[a[i]-'A'];
			else
				++ans;
		}
	}
	printf("%d",ans);
	return 0;
}
```
核心实现思想：使用 `cnt` 数组作为桶，通过字符的大小写判断是钥匙还是门，对钥匙数量进行增减操作。

### 关键思路或技巧
- 使用桶（数组或 `map`）来记录每种钥匙的数量，方便快速查找和更新。
- 贪心策略：钥匙能用就用，保证购买的钥匙数量最少。

### 拓展思路
同类型题可能会有不同的场景，如钥匙和门的对应规则变化、房间布局更复杂等，但核心思路仍然是使用贪心算法和桶来记录资源数量。

### 洛谷题目推荐
- P1090 [NOIP2004 提高组] 合并果子
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得摘录与总结
- 小恐：最后一个样例数错，以为看错题，看了好几遍题意，提醒我们在做题时要仔细检查数据和题意，避免因粗心导致错误。 

---
处理用时：39.63秒