# Schedule

## 题目描述

At the beginning of the new semester there is new schedule in the Berland State University. According to this schedule, $ n $ groups have lessons at the room 31. For each group the starting time of the lesson and the finishing time of the lesson are known. It has turned out that it is impossible to hold all lessons, because for some groups periods of their lessons intersect. If at some moment of time one groups finishes it's lesson, and the other group starts the lesson, their lessons don't intersect.

The dean wants to cancel the lesson in one group so that no two time periods of lessons of the remaining groups intersect. You are to find all ways to do that.

## 样例 #1

### 输入

```
3
3 10
20 30
1 3
```

### 输出

```
3
1 2 3 ```

## 样例 #2

### 输入

```
4
3 10
20 30
1 3
1 39
```

### 输出

```
1
4 ```

## 样例 #3

### 输入

```
3
1 5
2 6
3 7
```

### 输出

```
0
```

# 题解

## 作者：xiaozeyu (赞：3)

# **题目要使其余组的课程没有两个时间段相交**


**上代码。**
```c
#include<bits/stdc++.h>
using namespace std;
int l[5005],r[5005],s=0,sum[5005];
int n;
vector<int> ans;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)//输入
	{
		cin>>l[i]>>r[i];
		sum[i]=0;
	}
	for(int i=0;i<n;i++)//要双重
		for(int j=0;j<i;j++)
		{
			if(l[i]<r[j]&&l[j]<r[i])//判断是否要取消
			{
				sum[i]++;
				sum[j]++;
				s++;//计数
			}
		}
	for(int i=0;i<n;i++)
		if(sum[i]==s)
			ans.push_back(i+1);
	cout<<ans.size()<<endl;//输出
	for(int i=0;i<ans.size();i++)
		cout<<ans[i]<<" ";
}
```


---

## 作者：晨·曦 (赞：1)

### - 题意

给一个时间表，有 $n$ 个小组在一个房间上课。给出他们课程的起始时间 $a_i$   和终止时间 $b_i$，问能不能删去一个小组的课程，使其它小组的课程安排不冲突。

第一行输出方案数，第二行输出可以被删去的组的序号（升序）。

注意：如果在某个时刻，一组完成了课程，而另一组开始了课程，即 $b_i=a_{i+1}$ ，那么他们的课程不会相冲突。

### - 分析
双层循环去判断每一组的课程需不需要删掉。

其它题解好像说要用 _vector_ 来存，其实没有必要。$\because$ 方案数最多只有 $n$ 个，$\therefore$ 用 $l$ 来存方案数，用 $ans$ 数组来存可以被删掉的组的序号。
### - 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10010],b[10010],ans[10010],s[10010];
long long c,l;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
   // 双层循环 
	for(int i=1;i<n;i++) {
		for(int j=i+1;j<=n;j++) {
			if(a[i]<b[j]&&a[j]<b[i]) {
				s[i]++;
				s[j]++;
				c++;
			}
		}
	}
	for(int i=1;i<=n;i++) if(s[i]==c) ans[++l]=i;
	cout<<l<<"\n";
	for(int i=1;i<=l;i++) cout<<ans[i]<<" ";
	return 0;
}
```


---

## 作者：Buried_Dream (赞：0)

## 题意：
给定 $n$ 组课程，给你每组课程的起止时间，

找到所有的方案数使课程不交叉。

## 思路：

对于每种课都判断一下是否需要取消，用 $sum$ 数组来存。

判断完之后从前枚举一边，将答案放到一个数组中。

因为不知道有多少种，用 `vector` 来存。

注意下标从 $0$ 开始，放入的时候因该放入 $i + 1$。

## AC code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define down 0.996
#define T 252
#define lim 1e-15
#define orz cout << "szt lps fjh AK IOI";
using namespace std;

const int maxn = 3e6;
const int MAXN = 3e3;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (!isdigit(ch)) {if(ch == '-') {w = -1;}ch = getchar();}
	while (isdigit(ch)) {s = (s << 1) + (s << 3) + (ch ^ 48);ch = getchar();}
	return s * w;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}

vector <int> Ans;
int sum[maxn], js = 0;
int a[maxn], b[maxn];

signed main() {
	int n = read();
	for(int i = 0; i < n; i++)  a[i] = read(), b[i] = read();
	for(int i = 0; i < n; i++) 
		for(int j = 0; j < i; j++) 
			if(a[i] < b[j] && a[j] <b [i]) { 
				sum[i]++, sum[j]++, js++;
			}
	for(int i = 0; i < n; i++) if(sum[i] == js) Ans.push_back(i+1);
	cout << Ans.size() << endl;
	for(int i = 0; i < Ans.size(); i++)
		cout << Ans[i] << " ";
	return 0;
}


```


---

## 作者：jxbe6666 (赞：0)

### 题意：要使 $n$ 组的课程没有两个时间段相交。
-----

### 思路：
对于每种课都判断一下是否需要取消，用 $\text{sum}$ 数组来存。判断完之后从前枚举一边，将答案放到一个数组中。因为不知道有多少种，用 $\text{vector}$ 来存。

注意下标从 0 开始，放入的时候因该放入 $\text{i + 1}$。

-----

### 代码：
-----
```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x = 0, y = 1;
    char c = getchar();
    while (!isdigit(c))
    {
        y = (c == '-') ? -1 : 1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = (x << 1) + (x << 3) + c - '0';
        c = getchar();
    }
    return x * y;
}
int l[5005], r[5005], s = 0, sum[5005];
int n;
vector<int> ans; // vector
int main()
{
    n = read();
    for (int i = 1; i <= n; i++)
    {
        l[i] = read(), r[i] = read(), sum[i] = 0;
    }
    for (int i = 1; i <= n; i++) //要双重循环
        for (int j = 1; j < i; j++)
        {
            if (l[i] < r[j] && l[j] < r[i]) //判断是否要取消
            {
                sum[i]++;
                sum[j]++;
                s++;
            }
        }
    for (int i = 1; i <= n; i++)
        if (sum[i] == s)
            ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}

```

---

