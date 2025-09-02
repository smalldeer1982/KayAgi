# Meeting

## 题目描述

A 公司的一个项目团队中一共有 $(n+1)$ 个人，他们分别是领导以及编号从 $1$ 到 $n$ 的 $n$ 名员工。接下来的 $d$ 天中，领导会在其中的两天召开会议，向这两天到岗的员工传达一个重要事项。现在领导手里已经拿到了所有员工的出勤计划，他想让你帮他看看，最多能向多少员工（不含领导自己）传达这个重要事项？

## 说明/提示

#### 【输入输出样例 #1 解释】

在第 $2$ 天开会，将事项传达给员工 $1$；然后再在第 $3$ 天开会，将事项传达给员工 $1$ 和 $2$。

#### 【输入输出样例 #2 解释】

假设在第 $2,3$ 天开会，那么知道重要事项的员工只有员工 $1,3$。可以证明不可能所有人都会收到重要事项，所以正确答案为 $2$。

#### 数据规模与约定

所有测试点的输入数据保证：

- $1 \le n \le 10$，$2 \le d \le 10$，且 $n,d$ 均为整数；
- 输入中的后 $d$ 行输入的均为一个长度为 $n$，且仅由`o`和`x`组成的字符串。

## 样例 #1

### 输入

```
2 3
xx
ox
oo```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
xox
oxx
xxo```

### 输出

```
2```

## 样例 #3

### 输入

```
5 4
oxxox
xoxxx
xxoxo
oxxxo```

### 输出

```
4```

# 题解

## 作者：lxyz (赞：2)

题目意思非常清楚，就不多说了。

---
### 思路
范围很小可以直接暴力，先枚举第一天再枚举第二天，但是要注意两天都参加的员工不要计算重复。


---
## code

```python
def main():
    n, d = map(int, input().split())
    a = [input().strip() for _ in range(d)]

    max_attendance = 0

    # 遍历所有日子的组合
    for i in range(d):
        for j in range(i + 1, d):
            # 使用集合来跟踪可以接收到消息的独特员工
            attendees = set()

            # 检查这两天的出勤情况
            for k in range(n):
                if a[i][k] == 'o' or a[j][k] == 'o':
                    attendees.add(k)  # 将员工索引添加到集合中

            # 更新最大出勤人数为集合的大小（独特员工数）
            max_attendance = max(max_attendance, len(attendees))

    print(max_attendance)  # 输出结果

if __name__ == "__main__":
    main()

```

---

## 作者：wuyouawa (赞：1)

### 题解：AT_cpsco2019_s4_b Meeting

[题目传送门](https://www.luogu.com.cn/problem/AT_cpsco2019_s4_b)

### 思路

本题的 $n,d \le 10$，因此可以采用暴力枚举的方法，由于只是选两天，所以可以先统计一天的，再统计另一天的。但是要注意，第一天的与第二天的不要重复计算，只要计算一次。

### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,sum,b[15][15],c[15][15],ma;
char a[15][15];
int main()
{
	cin>>n>>d;
    for(int i=1;i<=d;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>a[i][j];
        }
    }
    for(int i=1;i<=d;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[i][j]=='o')  b[i][j]=1;//b数组统计第i天有哪些员工能接受到这个重要事项，这是第一个开会的日子的 
        }
    }
    for(int i=1;i<=d;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(a[i][j]=='o')  c[i][j]=1;//c数组统计第i天有哪些员工能接受到这个重要事项， 这是第二个开会的日子的 
        }
    }
	for(int i=1;i<d;i++)
    {
        for(int j=i+1;j<=d;j++)
        {   
		    sum=0;//sum用来统计第i天和第j天有几个员工能接受到这个重要事项
        	for(int k=1;k<=n;k++)
        	{
        		if(c[i][k]==1||b[j][k]==1)   sum++;//有一个即可接受到 
        	}
			ma=max(ma,sum);//找最大值 
        }       
    }   
    cout<<ma<<endl;//输出
    return 0;
}
```
### 时间复杂度

时间复杂度为 $O(ND²)$，可通过本题。

---

## 作者：e_zhe (赞：1)

本题题意非常清楚，在此不赘述了。

### 思路分析

我们观察到 $N,D\le 10$，因此可以直接暴力枚举所有方案，若一个员工在两天里的任意一天出勤，就把当前方案的出勤人数 $+1$，最后输出所有方案中出勤人数的最大值即可。

细节内容见代码注释。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,d,ans;//ans 记录所有方案中出勤人数的最大值 
bool a[15][15];//a[i][j] 表示第 i 天第 j 个人是否出勤 
char ch;
int main(){
	cin>>n>>d;
	for(int i=1;i<=d;++i)
		for(int j=1;j<=n;++j){
			cin>>ch;
			if(ch=='o')a[i][j]=true;//标记出勤 
		}
	for(int i=1;i<d;++i)
		for(int j=i+1;j<=d;++j){
			int sum=0;
			for(int k=1;k<=n;++k)if(a[i][k]||a[j][k])++sum;//两天中任意一天出勤，人数 +1 
			ans=max(ans,sum);
		}
	cout<<ans;
	return 0;
}
```

### 时间复杂度分析

时间复杂度为 $O(ND^2)$，可以通过此题。

---

## 作者：Akaurora (赞：1)

### 题目解析
-----------------------------
题目要求的是两天时间，而 $n$ 和 $d$ 都小于 10，这是个很小的数值。

因此不妨直接暴力。两天有一天出勤就记录，最后比较人数最大值即可。

### 个人代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define st string
st s[20];
ll n,d;
ll ans=0;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>d;
	for(int i=0;i<d;i++) cin>>s[i];
	for(int i=0;i<d;i++){
		for(int j=i+1;j<d;j++){
			ll p=0;
			for(int k=0;k<n;k++){
				if(s[i][k]=='o'||s[j][k]=='o') p++;
			}
			ans=max(ans,p);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：MingRi_Doctor (赞：0)

## 思路：
题目的数据范围很小，直接暴力枚举第一天和第二天开会的时间。看这两天都能有多少人出勤，输出最大出勤人数即可。
## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,ma,t //ma记录最大出勤人数，t计算开会两天的出勤人数
char a[15][15];
int main(){
	cin>>n>>d;
	for(int i=0;i<d;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}
	for(int i1=0;i1<d;i1++)//枚举第一天的开会时间
	{
		for(int i2=i1+1;i2<d;i2++)//枚举第二天的开会时间
		{
			for(int j=0;j<n;j++)//计算第i1天和第i2天都能有几个人出勤
			{
				if(a[i1][j]=='o'||a[i2][j]=='o') t++;//只要第j个人在其中一天有出勤，出勤人数加1
			}
			if(t>ma) ma=t;//看这两天的出勤人数有没有超过出勤人数的最大值，如果有，就将出勤人数的最大值设为t
			t=0;//t每次都要清零
		}
	}
	cout<<ma<<endl//记得换行
	return 0;
} 
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/AT_cpsco2019_s4_b)

此题数据很小，直接暴力枚举就行，两天只要有一天出勤数量就加一，然后比较出人数的最大值，最后输出。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n,d;
	cin >>n>>d;
	char a[d+1][n+1];
	int s=0,ma=-1;
    //ma用来统计最大值，初值小一点 
	for(int i=1;i<=d;i++){
        for(int j=1;j<=n;j++){
            cin >>a[i][j];
        }
    }
	for(int i=1;i<d;i++){
        for(int j=i+1;j<=d;j++){   
		    int s=0;//s用来统计第i天和第j天有几个员工可以接受到这个重要事项，每次都要变回零 
        	for(int k=1;k<=n;k++){
        		if(a[i][k]=='o'||a[j][k]=='o'){//有一个就能接受到，数量加一 
					s++;//加一 
				}
        	}
			ma=max(ma,s);//max(a,b)可以取a和b的最大值，这里是如果s比之前的最大值还大，就替换最大值 
        }
    }   
    cout<<ma<<endl;//输出最大值，AT要加换行 
	return 0;
}
```

---

## 作者：renzhanwen (赞：0)

这道题目的数据范围不大，可以直接进行**暴力枚举**。枚举任意两天里一共有多少员工会出勤，**注意：可能有一位员工两天都出勤，这时只能加一次。**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,sum;
bool vis[15][15];//全局变量初始值为false
int main()
{
	cin>>n>>d;
	for(int i=1;i<=d;i++)
		for(int j=1;j<=n;j++)
		{
			char x;
			cin>>x;
			if(x=='o')
				vis[i][j]=true;//标记第i天第j名员工出勤
		}
	for(int i=1;i<=d;i++)
		for(int j=i+1;j<=d;j++)
		{
			int m=0;
			for(int k=1;k<=n;k++)
				if(vis[i][k]||vis[j][k])//如果第i天或第j天第k名员工出勤了
					m++;
			sum=max(sum,m);
		}
	cout<<sum<<endl;
    return 0;
}
```

---

