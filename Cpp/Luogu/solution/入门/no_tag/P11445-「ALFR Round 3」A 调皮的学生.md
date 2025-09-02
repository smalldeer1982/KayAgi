# 「ALFR Round 3」A 调皮的学生

## 题目背景

在小山所在的学校中，有着一群非常调皮的学生。比如，在给老师的教学水平评分时，他们常常会给出不正经的评分。

## 题目描述

又到了一学期一度的评分大赛，每位同学都可以为本班某门科目的老师评分（一共有语、数、英三门科目）。每位同学应当只为一位老师评分。但有些学生常常会为多位老师评分，或者不为任何老师评分，我们称这样的学生为调皮的学生。现在给出小山所在班级的三门科目的老师的评分情况，请你求出该班级的调皮的学生的数量。

## 说明/提示

### 样例解释

学号为 $1,2,3,4,5$ 的学生分别为 $2,2,3,0,1$ 位老师评了分，学号为 $1,2,3,4$ 的学生都是调皮的学生，所以答案为 $4$。

### 数据范围

| 子任务 | 分值 | 限制 |
| :----------: | :----------: | :----------: |
| $0$ | $10$ | $n=1$ |
| $1$ | $20$ | $x,y,z$ 三个数组中的**所有**元素互不重复|
| $2$ | $10$ | $a=b=c=1$|
| $3$ | $10$ | $a=n,b=c=1$|
| $4$ | $20$ | $x,y,z$ 数组分别按照升序顺序给出|
| $5$ | $30$ | - |

对于 $100\%$ 的数据，$1\le n\le 100$，$0\le a,b,c\le n$，$1\le x_i,y_i,z_i\le n$，$x,y,z$ 数组内各自没有重复元素。

## 样例 #1

### 输入

```
5
3
2 3 5
2
3 1
3
1 2 3```

### 输出

```
4```

# 题解

## 作者：szh_AK_all (赞：8)

首先可以用一个桶 $t$ 来记录每个学生投票的次数，再枚举每位学生，若这位学生的投票次数小于 $1$（没投）或者大于 $1$（投了多次），那么他便是一个调皮的学生。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t[105];

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= 3; i++) {
		int x;
		cin >> x;
		for (int j = 1; j <= x; j++) {
			int a;
			cin >> a;
			t[a]++;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (t[i] != 1)
			ans++;
	cout << ans;
}
```

---

## 作者：封禁用户 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P11445)

我们可以用一个桶来统计每名学生为多少个老师评了分，如果这名学生为多位老师评分或者不为任何老师评分，那么这名学生就是调皮的学生，统计数量输出即可。

```cpp
#include <iostream>
using namespace std;

const int N = 105;

int n, a, b, c, x[N], y[N], z[N], cnt[N];

int main()
{
	cin >> n >> a;
	for (int i = 1; i <= a; i++)
	{
		cin >> x[i];
        cnt[x[i]]++;
	}
	cin >> b;
	for (int i = 1; i <= b; i++)
	{
		cin >> y[i];
        cnt[y[i]]++;
	}
	cin >> c;
	for (int i = 1; i <= c; i++)
	{
		cin >> z[i];
        cnt[z[i]]++;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
        if (cnt[i] > 1 || cnt[i] == 0) ans++; // 为多位老师评分或者不为任何老师评分
	cout << ans;
	return 0;
}
```

---

## 作者：This_is_my_choice (赞：4)

首先在输入时使用一个数组记录这个学生对哪几位老师评了分，然后判断是否只有一个学生对这个老师评了分，如果不是，调皮的学生就加一。

代码奉上：

```
#include<bits/stdc++.h>
using namespace std;
int l[5];
int main(){
    int n;
    cin>>n;
    int a;
    cin>>a;
    for(int i=1;i<=a;i++){
        int x;
        cin>>x;
        l[x]++;
    }
    int a2;
    cin>>a2;
    for(int i=1;i<=a2;i++){
        int x;
        cin>>x;
        l[x]++;
    }
    int a3;
    cin>>a3;
    for(int i=1;i<=a3;i++){
        int x;
        cin>>x;
        l[x]++;
    }
    int s=0;
    for(int i=1;i<=n;i++){
        if(l[i]!=1){
            s++;
        }
    }
    cout<<s;
    return 0;
} 
```

---

## 作者：__Wanna__Accepted__ (赞：4)

~~蒟蒻来写题解了！~~

## P11445 「ALFR Round 3」A 调皮的学生

### 做题思路

本题用桶统计每位学生给几位老师投了票，统计调皮的学生数量为投 $0$ 票或大于 $1$ 票的。

初始化答案为 $n$，之后对于每一次投票，让该学生的桶数量加 $1$。如果此时他/她的桶为 $1$，则让答案减 $1$（原先这个人投的是 $0$ 票），否则如果此时是 $2$ 让答案加 $1$（原先的一个好学生~~堕落了~~）。输出最终的答案即可。

### 正确代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,t[101];
int main(){
    cin>>n;
    int ans=n;//初始答案
    for(int i=1;i<=3;i++){//由于有三个老师，循环三遍
        cin>>a;
        while(a--){
            int x;
            cin>>x;
            t[x]++;//记录桶
            if(t[x]==1)ans--;
            else if(t[x]==2)ans++;
        }
    }
    cout<<ans;
    return 0;
}
```

[这样就可以 AC 啦！](https://www.luogu.com.cn/record/195923234)请不要抄题解哦。

---

## 作者：cff_0102 (赞：4)

开个桶记录下每个学生给几个老师投票，最后再扫一遍记录下答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int a[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=3;i++){
		int x;cin>>x;
		while(x--){
			int y;cin>>y;
			a[y]++;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)if(a[i]!=1)ans++;
	cout<<ans;
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：2)

题目传送门：[P11445 「ALFR Round 3」A 调皮的学生](https://www.luogu.com.cn/problem/P11445)

~~为什么会有每位同学只应该为一位老师评分这种规则啊。~~

### 题目做法

用桶计数就是可以开一个数组，这个数组的第 $i$ 位表示第 $i$ 个学生投的票数。这样我们就可以对于每次输入，直接让对应下标位置加 $1$ 以维护。

我们用最简单~~醋包~~的方法开桶、存每个学生投的票数，统计有多少个学生投的不是 $1$ 票即可。

### AC 代码

```cpp
#include<iostream>
using namespace std;
int n,a,b,c,sum[101],ans;
int main(){
	cin>>n;
	cin>>a;//语文老师
	for(int i=1,x;i<=a;sum[x]++,i++)cin>>x;
	cin>>b;//数学老师
	for(int i=1,y;i<=b;sum[y]++,i++)cin>>y;
	cin>>c;//英语老师
	for(int i=1,z;i<=c;sum[z]++,i++)cin>>z;
	for(int i=1;i<=n;i++)ans+=(sum[i]!=1);//统计答案
	cout<<ans;
	return 0;
}
```

[容易 AC](https://www.luogu.com.cn/record/195567804)。

---

## 作者：dalu (赞：2)

开个桶记录一下每个学生给几个老师投了票，统计桶里面不为 $1$ 的数有几个。
```cpp
#include <iostream>
using namespace std;

int cnt[105];
int n,m,x,ans;

int main(){
    cin >> n;
    cin >> m;
    for(int i = 1;i <= m;i++) cin >> x,cnt[x]++;
    cin >> m;
    for(int i = 1;i <= m;i++) cin >> x,cnt[x]++;
    cin >> m;
    for(int i = 1;i <= m;i++) cin >> x,cnt[x]++;
    for(int i = 1;i <= n;i++) if(cnt[i] != 1) ans++;
    cout << ans;
    return 0;
}
```

---

