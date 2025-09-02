# [CCC 2020] Epidemiology

## 题目背景

本题译自 [Canadian Computing Competition](https://cemc.uwaterloo.ca/resources/past-contests?contest_category=29) [2020 Junior](https://cemc.uwaterloo.ca/sites/default/files/documents/2020/2020CCCJrProblemSet.html) T2 Epidemiology。

## 题目描述

当一个人患病时，他会在明天感染 $R$ 个人，随后便不再感染他人。没有一个人会被感染超过一次。我们想要确定造成 $P+1$ 个人患病的最早时间。

## 说明/提示

**本题采用捆绑测试**。
#### 【样例解释】
对于第一组样例，第 $4$ 天共感染了 $1+5+25+125+625=781$ 人，且 $781 >750$。可证明这是最早时间。

对于第二组样例，第 $5$ 天共感染了 $2+2+2+2+2+2=12$ 人，且 $12 >10$。可证明这是最早时间。

## 样例 #1

### 输入

```
750
1
5```

### 输出

```
4```

## 样例 #2

### 输入

```
10
2
1```

### 输出

```
5```

# 题解

## 作者：CSP_S_2023_T2 (赞：5)

#### 思路

分析题目：

第 $0$ 天：已感染人数 $n$ 人。

第 $1$ 天：新增人数为 $nr$ 人，已感染人数为 $n+nr$ 人。

第 $2$ 天：新增人数为 $nr^2$ 人，已感染人数为 $n+nr+nr^2$ 人。

第 $x$ 天：新增人数为 $nr^x$ 人，已感染人数为 $n \times \sum_{i=0}^{x} r^i$ 人。

所以我们只需找到一个最小的 $x$ ，使得 $n \times \sum_{i=0}^{x} r^i$ 大于等于 $p+1$ 即可。

#### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int p,n,r,days,cnt;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>p>>n>>r;
	cnt=n;          //cnt 为已感染人数 
	while(cnt<=p){
		n*=r;       //更新新增感染人数 
		cnt+=n;     //更新已感染人数 
		days++;     //增加天数 
	}
	cout<<days;
	return 0;
}
```

---

## 作者：zyxjeek (赞：0)

## 1.题目描述

有 $N$ 个人在第 $0$ 天患病。当一个人患病时，他会在明天感染 $R$ 个人，随后便不再感染他人。没有一个人会被感染超过一次。我们想要确定造成 $P+1$ 个人患病的最早时间。

## 2.思路

简单模拟即可。我们用变量 $d_i$ 记录第 $i$ 新增的患病人数，由于每人能感染 $R$ 人，所以 $d_i = d_{i-1} \times R$。不断让 $N$ 加上 $d_i$，直到 $N > P$。此时的天数 $i$ 就是答案。

## 3.注意事项

- 退出循环时，$i$ 的值是感染 $P$ 个人后的第二天。所以答案是 $i-1$。

## 4.代码

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p, n, r;
    cin >> p >> n >> r;
    int d = n, i;
    for (i = 1; n <= p; i++) {
        d *= r;
        n += d;
    }
    cout << i-1 << endl;
    return 0;
}
```

## 5.时间复杂度

循环变量 $d$ 在每次循环中都会乘上 $R$，所以时间复杂度是 $\mathcal O(\log_R P)$。



---

The End

---

## 作者：Stars_Traveller (赞：0)

## 题解：P11577 [CCC2020] Epidemiology
### 思路
一眼题。

有 $n$ 个人在第 $0$ 天被感染，$n \times r$ 个人在第 $1$ 天被感染，$n\times r^2$ 个人在第二天被感染。

则第一天总感染人数为 $n \times r +n$，第二天总感染人数为 $n\times r^2+n\times r+n$，以此类推，累加总感染人数直到第一次 $> p$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int p, n, r, now, all, ans;
signed main()
{
	cin>>p>>n>>r;
	now=r*n, all=n, ans;
	while(all<=p)
	{
		++ans,all+=now;
		now*=r;
	}
	cout<<ans;
}

---

## 作者：DashZhanghanxu (赞：0)

# 解析
首先，先输入。然后判断要查询的人是否感染，如果是，输出一并结束代码。若不是，继续模拟每日感染情况，每次循环先将天数加一，然后模拟每日新增感染人数，将总感染人数加上新增人数，并判断当前要查询的人是否感染，如果是，则结束循环，并输出当前天数。
# CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll p,n,r;
	cin>>p>>n>>r;
	if(n==p){
		cout<<1;
		return 0;
	}
	ll all=n;
	ll day=0;int zt=n; 
	while(++day){
		zt=zt*r;
		all=all+zt;
		if(all>p)break;
	}cout<<day;
	return 0;
} 
```

---

