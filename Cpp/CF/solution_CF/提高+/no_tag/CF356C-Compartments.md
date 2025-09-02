# Compartments

## 题目描述

一支来自$S$市的学生队伍被派去参加柏林信息学奥林匹克竞赛。他们乘火车去到那里，所有学生都买了一节车厢的票，车厢由$n$个隔间组成（每个车厢正好有4个人）。我们知道，如果一个隔间里只有一两个学生，那么他们会感到无聊；如果一个包厢里有三到四个学生，那么这个包厢在整个旅程中都会欢歌笑语。

同学们都想和别人交换，这样就没有一个隔间里的学生会无聊了。要想和另一个人交换位置，你需要让他相信这是很必要的。学生们无法独立地找到必要的论据，所以他们向一位富有同情心的售票员寻求帮忙。售票员可以用她的生活经验说服任何乘客跟任何学生交换位置。

然而，售票员不想浪费时间去说服不用换位的人，所以她想知道说服乘客和学生换位所需的最少次数是多少。你的任务是找到这个**最小次数**。

在所有的换座完了之后，每个隔间要么没有学生，要么有三四个学生。

## 样例 #1

### 输入

```
5
1 2 2 4 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
4 1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
0 3 0 4
```

### 输出

```
0
```

# 题解

## 作者：FiraCode (赞：2)

## 思路
$p_i$ 表示i的出现次数。

当 $\sum a_i < 3$ 或 $\sum a_i = 5$ 就是 `-1`。


当 $p_1 \ge p_2$

答案加上 $p_2$。

答案再加上 $\frac{p_1}{3} \times 2$，因为三个合并成一个，要合并两次，所以要再乘 $2$。

当 $p_1 = 1$

当 $p_3 \not = 0$

答案加一，把这个 $1$ 放到一个三里面。

否则答案加二，因为要把两个 $4$ 每个拿出一个 $1$ 给他，所以有两次。

当 $p_1=2$

答案加上 $2$，因为要么是把他两个合并，一次在把一个 $4$ 里拿出一个 $1$，或者把他们分别合成在一个三里，所以都是需要两次。

然后当 $p_1 < p_2$ 类似的搞一搞就好了。

## CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int n;
int a[N], p[N];//p[i]表示i的出现次数
int main() {
    scanf("%d", &n);
    int sum = 0;//总和最多是4*10^6
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
        p[a[i]]++;
    }
    if (sum == 1 || sum == 2 || sum == 5) {//sum不够3个，或分不成3个和4个
        puts("-1");
        return 0;
    }
    int ans = 0;
    if (p[1] >= p[2]) {
        ans += p[2];
        p[1] -= p[2];//把p[2]个2和p[2]个1构成三个
        ans += p[1] / 3 * 2;//要把p[1]里三个合成一个，因为要说服另外两个，所以再乘2
        p[3] += p[1] / 3;//3的个数加上它里面有多少个。
        p[1] %= 3;
        if (p[1] == 1) {
            if (p[3] >= 1)
                ans++;//表示有一个3，可以直接说服，然后把他放到某个有三个人的房间里。
            else
                ans += 2;//否则就要把两个4每一个都说服一个来。
        }else if (p[1] == 2)
            ans += 2;//因为不管是把两个一合并到一个，再从四里拿过来一个，还是
    }else {//同1的处理方法
        ans += p[1];
        p[2] -= p[1];
        ans += p[2] / 3 * 2;
        p[3] += p[2] / 3;
        p[2] %= 3;
        if (p[2] == 1) {
            if (p[4] >= 1)
                ans += 1;
            else
                ans += 2;
        }
        else if (p[2] == 2)
            ans += 2;
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：wky32768 (赞：2)

这是一道毒瘤特判全是判断代码毫无含量你还会非常崩溃的WA在一百多的点的毒瘤题目。

你需要分情况讨论并全部写对，从上面你已经能看出来这需要高超的（分类讨论）技巧。

下面的代码可能能够给你一些策略上的启发，不过没有仔细想的话最好先不要看这篇题解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int one, two, three, four, n;
int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		if (x == 1) one++;
		if (x == 2) two++;
		if (x == 3) three++;
		if (x == 4) four++;
	}
	int ans = 0;
	if (one >= two) {
		one -= two;
		ans += two;
		three += two;
		two = 0;
		three += one / 3;
		ans += one / 3 * 2;
		one %= 3;
		if (one == 0) goto L1;
		if (one <= three) {
			three -= one;
			four += one;
			ans += one;
			one = 0;
		} else {
			if (one == 2) {
				if (four >= 1) {
					four -= 1;
					one -= 2;
					ans += 2;
					three += 1;
				} else if(three>=2) {
					three-=2;
					four+=2;
					ans+=2;
				} else{
					cout << "-1";
					return 0;
				}
			} else if (one == 1) {
				if (four >= 2) {
					four -= 2;
					one--;
					three++;
					ans += 2;
				} else {
					cout << "-1";
					return 0;
				}
			}
		}
L1:
		cout << ans;
		return 0;
	} else {
		two -= one;
		ans += one;
		one = 0;
		three += two / 3 * 2;
		ans += two / 3 * 2;
		two %= 3;
		if (two == 0) goto L2;
		if (two == 1) {
			if (four >= 1) {
				four--;
				two--;
				three++;
				ans++;
			} else if (three >= 2) {
				three -= 2;
				four += 2;
				two--;
				ans += 2;
			} else {
				cout << "-1";
				return 0;
			}
		} else if (two == 2) {
			four++;
			two -= 2;
			ans += 2;
		}
L2:
		cout << ans;
		return 0;
	}
}

```
也没有那么毒瘤对吧（大雾

---

