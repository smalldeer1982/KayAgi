# [CCC 2023 J3] Special Event

## 题目描述

你正在尝试在五个可能的日子之一安排一个特别活动。你的任务是确定在哪一天安排活动，以便最多的感兴趣的人能够参加。

## 说明/提示

**本题采用捆绑测试**。- 子任务 $1$（$6$ 分）：有且只有一天全部人都可以开会。- 子任务 $2$（$6$ 分）：有且只有一天开会人数最多。- 子任务 $3$（$3$ 分）：有可能有多天满足条件。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
YY.Y.
...Y.
.YYY.```

### 输出

```
4```

## 样例 #2

### 输入

```
5
YY..Y
.YY.Y
.Y.Y.
.YY.Y
Y...Y```

### 输出

```
2,5```

# 题解

## 作者：Ayaka_Li (赞：8)

### 这是一道模拟题
思路：计算出每天的人数并保存，记录最大值对比有哪些天人数最多。

#### 输入
  ```cpp

      cin>>n;
      for (int i=1;i<=n;i++) {
          for (int j=1;j<=5;j++) {
              char c;
              cin>>c;
              if (c=='Y') f[i][j]=1;
              else f[i][j]=0;
          }
      }
  ```

#### 记录
  ```cpp
      for (int i=1;i<=5;i++) {
          int sum=0;
          for (int j=1;j<=n;j++) {
              sum+=f[j][i];//注意要计算每一列的
          }
          a[i]=sum;
          if (sum>=maxn)//更新
              maxn=sum;
      }
      for (int i=1;i<=5;i++)//保存
          if (a[i]==maxn) {
              d[++ans]=i;
      }


  ```
#### 输出
  ```cpp
      cout<<d[1];
      for (int i=2;i<=ans;i++)
          cout<<','<<d[i];//注意逗号


  ```
~~求过~~

---

## 作者：封禁用户 (赞：7)

## 分析

我们建立一个结构体来存每一天的能够开会的人数和这一天是星期几。在计算出每一天的能够开会的人数后，我们将这个结构体按照人数降序排序。注意，在排序的时候，若这两天人数一样，我们要优先考虑靠前的。排完之后，先输出排在第一位是星期几，在看后面的是否与其人数相同即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
char ch[1000][1000];
struct node{
	int ans,id;
}a[100000];
bool cmp(node a,node b)
{
	if(a.ans==b.ans) return a.id<b.id;
	else return a.ans>b.ans;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=5;i++) a[i].id=i;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=5;j++)
			cin>>ch[i][j];
	for(int j=1;j<=5;j++)
		for(int i=1;i<=n;i++)
			if(ch[i][j]=='Y') a[j].ans++;
	sort(a+1,a+5+1,cmp);
	cout<<a[1].id;
	for(int i=2;i<=5;i++)
		if(a[i].ans==a[1].ans) cout<<","<<a[i].id;
}
```
注：要注意输出哦。

---

## 作者：Night_sea_64 (赞：3)

这题很水。我们只用统计出每一天能到多少个人，把人数最多的天数都记录下来就好了。

统计最大值的时候，实时记录最大值和对应的天数。如果当前这一天的人数比最大值大，则更新最大值并把之前记录的天数清空。

我们需要用逗号隔开，所以我们需要提前知道最大值的数量，所以不能在统计的时候就输出。

```cpp
#include<iostream>
using namespace std;
char a[25][10];
int ans[10];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=5;j++)
            cin>>a[i][j];
    int cur=0,maxn=0;
    for(int i=1;i<=5;i++)
    {
        int cnt=0;
        for(int j=1;j<=n;j++)
            cnt+=(a[j][i]=='Y');
        if(cnt>maxn)cur=0,maxn=cnt;
        if(cnt==maxn)ans[++cur]=i;
    }
    for(int i=1;i<=cur;i++)
    {
        cout<<ans[i];
        if(i<cur)cout<<',';
    }
    return 0;
}
```

---

## 作者：wangyinghao (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9301)

一道模拟题，但有些地方很烦人，会分步去讲。

------------

### 前置内容

定义数组 $cnt$，$cnt_i$ 表示在第 $i$ 天能参加会议的员工的个数。

### Step 1 输入

这一部分边输入边判断字符是否为 $\texttt{Y}$，然后对 $cnt$ 进行处理。

```cpp
int n;
char c;
cin>>n;
for(int i=1;i<=n;i++){
	for(int j=1;j<=5;j++){
		cin>>c;
		if(c=='Y') cnt[j]++;//能参加会议 (cnt_j)+1
	}
}
```

### Step 2 判断最大值

为了之后的处理，我们要打擂台求**能参加会议最多的员工的那一天**的员工（有点绕）。

```cpp
int maxx=0;
for(int i=1;i<=5;i++) maxx=max(maxx,cnt[i]);
```

### Step 3

（标题没想好咋起）

这一步要知道有几天参加会议的员工是最多的，判断 $maxx$ 是否等于 $cnt_i$ 即可。

```cpp
int cnt1=0;
for(int i=1;i<=5;i++){
	if(maxx==cnt[i]) cnt1++;
}
```

### Step 4 输出

不好讲，在代码里解释。

```cpp
int cnt2=0;//用于进行输出判断
for(int i=1;i<=5;i++){
	if(maxx==cnt[i]){//是参加员工数量最多的一天
		cnt2++;//最大员工天数+1
		if(cnt2<cnt1) cout<<i<<",";//还没有到最后 要多输出逗号
		else cout<<i;//最后 不用输出逗号
	}
}
```

最后是完整代码。

```cpp
#include<iostream>
using namespace std;
int cnt[10];

int main(){
	int n;
	char c;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=5;j++){
			cin>>c;
			if(c=='Y') cnt[j]++;//能参加会议 (cnt_j)+1
		}
	}
	int maxx=0;
	for(int i=1;i<=5;i++) maxx=max(maxx,cnt[i]);
	int cnt1=0;
	for(int i=1;i<=5;i++){
		if(maxx==cnt[i]) cnt1++;
	}
	int cnt2=0;//用于进行输出判断
	for(int i=1;i<=5;i++){
		if(maxx==cnt[i]){//是参加员工数量最多的一天
			cnt2++;//最大员工天数+1
			if(cnt2<cnt1) cout<<i<<",";//还没有到最后 要多输出逗号
			else cout<<i;//最后 不用输出逗号
		}
	}
	return 0;
}
```

---

## 作者：Leaves_xw (赞：1)

**思路：**

每一次输入 $5$ 个字符，之后定义 $5$ 个计数器，如果字符是 `Y` 则将对应的计数器累加 $1$，最后给所有的计数器 `sort` 排序就可以通过啦。

**代码：**

主要判断部分：

```
int n,cnt[6];
cin>>n;
for(int i=1;i<=n;i++)
{
   char c[6];
   for(int j=1;j<=5;j++)
   {
        cin>>c[j];
        if(c[j]=='Y')cnt[j]++; 
   }
}
```

输出部分：

```
for(int i=1;i<=5;i++)
{
    if(cnt[i]==MAX)
    {
	if(flag==0)
        {
	    cout<<i;
	    flag=1;
        }
        else cout<<','<<i;
	}
}
cout<<endl;
```

---

## 作者：Hughpig (赞：0)

思路：

我是用 `string` 去存的，用一个 `vector` 记录答案的天数。

把所有字符串从 $0$ 到 总天数（即字符串长度）循环统计一遍，计算当天可以到场的员工个数，记作 $cnt$。把当前最大的到场人数记作 $maxx$。

如果 $cnt>maxx$，更新 $cnt$ 为 $maxx$，把目前所有答案清空，改为当前的天数。

如果 $cnt=maxx$，把当前天数加入答案。

最后输出答案，需要注意只要输出答案个数 $-1$ 个 `,` 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,cnt,maxx=-1;
string s[20];
vector<int>chosen;

int main()
{
	cin>>n;
	for(int i=0;i<n;i++)cin>>s[i];
	for(int i=0;i<s[0].size();i++)
	{
		cnt=0;
		for(int j=0;j<n;j++)
		{
			if(s[j][i]=='Y')cnt++;
		}
		if(cnt>maxx)
		{
			maxx=cnt;
			chosen.clear();
			chosen.push_back(i+1);
		}
		else if(cnt==maxx)
		{
			chosen.push_back(i+1);
		}
	}
	for(int i=0;i<chosen.size()-1;i++)cout<<chosen[i]<<',';
	cout<<chosen[chosen.size()-1];
}
```

---

## 作者：yzm0325 (赞：0)

主要思路就是先循环统计每天的开会人数，然后打擂台找到最大值，再找到哪些天是最大值，用逗号隔开输出即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[6], maxn[6], maxnum, cnt;
char c;
int main() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= 5; j++) {
            cin >> c;
            if(c == 'Y') a[j]++;
        }
    for(int i = 1; i <= 5; i++) if(a[i] > maxnum) maxnum = a[i]; // 统计最大值。
    for(int i = 1; i <= 5; i++) if(a[i] == maxnum) maxn[++cnt] = i; // 统计哪几天是最大值。
    for(int i = 1; i < cnt; /*最后一个数不能带逗号。*/ i++) cout << maxn[i] << ",";
    cout << maxn[cnt]; // 输出最后一个数。
    return 0;
}
```

upd：刚刚自己发现了一个代码的小错误，已改正，麻烦过一下，谢谢！

---

## 作者：maomao233 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9301)

### 简化题意

输入一个 $n\times 5$ 的矩阵，请你计算并输出哪一列的 `Y` 最多，如果有多列，以一个 `,` 间隔。

### 分析

我们可以定义一个数组 $b$ 来存储每列的 `Y` 的数量。

先用 for 循环扫 $5$ 遍，第 $i$ 遍统计那一列 `Y` 的数量，将其赋值给 $b_i$。同时，我们还需定义一个变量 $maxn$，以要求出 $5$ 列中 `Y` 的最大数量。

总体代码长这样：

```cpp
int maxn=0;
for(int j=1;j<=5;j++)
{
	for(int i=1;i<=n;i++)
	{
		b[j]+=a[i][j]=='Y';
	}
	maxn=max(maxn,b[j]);
}
```

接着，我们再定义一个存储答案的数组 $ans$。

继续用 for 循环扫 $5$ 遍，判断第 $i$ 天的 `Y` 的数量是否最大，即是否 $=maxn$。如果是，就将其存入 $ans$ 数组里。具体实现看代码：

```cpp
int cnt=0; //存储数组 ans 的大小。同理，也可以使用 vector 来存储。
for(int i=1;i<=5;i++)
{
	if(b[i]==maxn)
	{
		cnt++;
		ans[cnt]=i; //模拟 vector 存储
	}
}
```

最后输出 $ans$ 数组即可。注意，输出的时候也分两种情况：$i<cnt$ 或 $i=cnt$。第一种，输出完 $ans_i$ 后还需输出一个 `,`；第二种，不用输出 `,`。所以输出的时候还需要判断一下。同理，这个判断过程也可以使用[三目运算符](https://baike.baidu.com/item/%E6%9D%A1%E4%BB%B6%E8%BF%90%E7%AE%97%E7%AC%A6/6180633)优化：

```cpp
cout<<ans[i]<<((i<cnt)?',':'\n');
```

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[21][5];
int b[5];
int ans[21];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=5;j++)
		{
			cin>>a[i][j];
		}
	}
	int maxn=0;
	for(int j=1;j<=5;j++)
	{
		for(int i=1;i<=n;i++)
		{
			b[j]+=a[i][j]=='Y';
		}
		maxn=max(maxn,b[j]);
	}
	int cnt=0;
	for(int i=1;i<=5;i++)
	{
		if(b[i]==maxn)
		{
			cnt++;
			ans[cnt]=i;
		}
	}
	for(int i=1;i<=cnt;i++)
	{
		cout<<ans[i]<<((i<cnt)?',':'\n');
	}
	return 0;
}
```


---

## 作者：CleverRaccoon (赞：0)

## 题目

[题目传送门](https://www.luogu.com.cn/problem/P9301)

## 思路

1. 记录：因为要统计哪天来的人数最多，所以用一个长度为 $5$ 的数组来记录每天的人数：

```cpp
const int N = 6;	// 数组多开一点儿
int a[N];
```

2. 输入：因为输入的是单字符，所以直接 `cin` 就可以了，使用 `getchar` 或者 `scanf` 有可能会出问题，每次输入时，如果某个人第 $i$ 天字符是 `Y`，就把统计数量的数组的第 $i$ 项加一：

```cpp
for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= 5; ++j) {
        char c;
        cin >> c;
        // c == 'Y'时返回值是1，反之则返回值为0，所以有了以下的写法。
        a[j] += c == 'Y';
        // 等同于:
        // if(c == 'Y')	++a[j];
    }
```

3. 取最大值：

用一个变量来记录最大值，初始化为 $0$，遍历刚刚记录好的统计数组，依次进行比较，最终取得最大值：

```cpp
int maxd = 0;
for(int i = 1; i <= 5; ++i)
    maxd = max(maxd, a[i]);
```

4. 输出答案：

要判断最大值在哪几天里，所以，循环遍历统计数组，如果第 $i$ 项与最大值相同，则输出 $i$：

```cpp
bool flag = false;
for(int i = 1; i <= 5; ++i)
   if(a[i] == maxd)
       if(flag)
          cout << ',' << i;
       else
          cout << i, flag = true;
```

这里有一个小细节，也就是输出时，如果第一次输出，则不需要输出 `,`，故需要记录一下是否为第一次输出。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 6;
int a[N];

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= 5; ++j) {
            char c;
            cin >> c;
            a[j] += c == 'Y';   // 统计每个人的情况
        }
    int maxd = 0;
    for(int i = 1; i <= 5; ++i) // 取最大值
        maxd = max(maxd, a[i]);
    bool flag = false;  // 输出格式化
    for(int i = 1; i <= 5; ++i)
        if(a[i] == maxd)    // 如果是最大值
            if(flag)    // 之前输出过
                cout << ',' << i;
            else    // 第一次输出
                cout << i, flag = true;
    return 0;
}
```

完结撒花！谢谢大家！


---

## 作者：Red0rangE (赞：0)

## 题意理解

给出一个正整数 $n$，再给出一个 $n$ 行 $5$ 列的字符阵。要求找出 ```Y``` 数量最多的一列并输出列号，如果数量相同则用逗号隔开一起输出。

## 思路阐述

遍历每一列，找出每一列 ```Y``` 的数量并记录比较。具体见代码注释。

## 代码呈现

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
bool mp[22][6];//字符阵
string s;
int mx=-1;//初始设定最多的有-1个Y
int k;//答案数量
int ans[6];//答案

signed main(){
    
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        cin>>s;
        for (int j=1;j<=5;j++)
            if (s[j-1]=='Y')//输入是Y
                mp[i][j]=1;//标记为true
    }//输入结束
    for (int i=1;i<=5;i++){//遍历每一列
        int cnt=0;//初始计数为0
        for (int j=1;j<=n;j++)
            if (mp[j][i])//是Y
                cnt++;//计数加一
        if (cnt>mx){//比现有最大值大
            mx=cnt;//更新最大值
            k=0;//重置答案数量
            ans[++k]=i;//加入答案
        }
        else if (mx==cnt)//与记录相同
            ans[++k]=i;//加入答案
    }
    printf("%d",ans[1]);//先输出一个
    for (int i=2;i<=k;i++)
        printf(",%d",ans[i]);//后边的补上逗号输出
    return 0;
    
}

```

希望可以帮到各位大佬。

---

