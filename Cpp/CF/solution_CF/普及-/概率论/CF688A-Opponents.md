# Opponents

## 题目描述

# 问题描述

小白有 n 个对手，他每天都要和这些对手PK。对于每一天，如果 n 个对手全部到齐，那么小白就输了一场，否则小白就赢了一场。特别的，如果某天一个对手都没有到，也算小白赢。现在已知对手 d 天的出场情况，请计算小白最多能连胜多少场。

## 样例 #1

### 输入

```
2 2
10
00
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 1
0100
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 5
1101
1111
0110
1011
1111
```

### 输出

```
2
```

# 题解

## 作者：Register (赞：3)

# 怎么大佬们的题解都那么长。。。
这道题就是个贪心，有点类似于最大子段和的感觉，下面是解题思路：
	
    有一个统计当前连胜的变量和统计最高连胜的变量
    如果此次是胜利的，那么当前连胜++，并与总连胜作比较
    否则，当前连胜清零
这样贪心一定能保持最优解。（小学生都懂得起）

代码如下：
```cpp
#include <iostream>//输入输出流库
#include <algorithm>//max()需要的库
using namespace std;//max()和cin、cout需要这个	
int main(){
	int maxn=0/*最高连胜*/,d,n,sum=0/*当前连胜*/;
	char t;
	cin>>n>>d;
	while(d--)
	{
		bool flag=false;//判断是否胜利
		for(int i=1;i<=n;i++)
		{
			cin>>t;
			if(t=='0') flag=true;//有0就一定赢了
		}
		if(flag) {sum++;maxn=max(sum,maxn);}//更新当前or最高连胜
		else sum=0;//输了，当前连胜清零
	}
	cout<<maxn<<endl;
	return 0;
}
```

---

## 作者：judgejudge (赞：2)

# 通俗易懂！！！
这道题注意：**让我们查找连续赢多少场**。

首先，**我们可以把每一天的情况转换成赢或输的形式，如果赢，连续场数++，输的话就清零，然后查找最大值。**

问题是怎样确定赢或输？？？

大家别忘了字符串当中有一个叫做**find函数**。

我们只需要**查找是否出现0**，如果有，认为比赛胜利，没有就认为比赛失败。

那么就有了AC代码：
```cpp
#include <iostream>
#include <string>
using namespace std;
string st;
int main(){
	int i,j,k,n,m;
	int sum=0,tot=0;//分别定义最大值和连续胜场
	cin>>n>>m;
	for(i=1;i<=m;i++){
		cin>>st;//输入字符串
		k=st.find('0');//查找是否有0
		if(k>=0)tot++;//如果有，连胜场数++
		else tot=0;//没有则清零
		sum=max(sum,tot);//进行一次最大值比较
	}
	cout<<sum<<endl;//输出最大值
	return 0;//程序结束
}
```




---

## 作者：LevenKoko (赞：1)

# [戳我获得更好的观影效果](https://www.cnblogs.com/zhenglw/p/9517670.html)
### 【思路分析】

#### 比较水的模拟题
####具体见代码吧

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){
	char chr = getchar();	int f = 1,ans = 0;
	while(!isdigit(chr)) {if(chr == '-') f = -1;chr = getchar();}
	while(isdigit(chr))  {ans = ans * 10;ans += chr - '0';chr = getchar();}
	return ans* f ;
}
void write(int x){
	if(x < 0) putchar('-'),x=-x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int sum[105],a[105][105];
int n,m;
int main(){
	n=read();
	m=read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)
			scanf("%1d",&a[i][j]),sum[i]+=a[i][j];//读入...
		if(sum[i]==n) sum[i]=0; else sum[i]=1;//某一行若全是1，那么记为1，否则为0
	}
	int len=0,ans=0;//ans记录答案,len记录当前连续1的长度
	for(int i=1;i<=m;i++){
		if(sum[i]==1)	len++,ans=max(len,ans);//只要某一行全是1，就和ans判断取最大值
		else len=0;//一旦有中断，就清空当前连续1的长度
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：ZolaWatle (赞：0)

### CF688A 题解

### 思路：字符串

其实本题的题意十分明确，只有像**1111111111**这样的字符串才能终结我们主角的连胜。

所以，我们边读边判断输入的字符串是**否全为1**即可（只要有一个是零便不全为1）。如果并不是，说明对手没来齐，加一场连胜；如果全为一，那么就将当前的连胜数清零。

当然，每清一次零，都要与当前的最大连胜场数进行比较，以更新答案。

具体实现过程**看代码**（还会讲到一些细节问题）：

```cpp
#include <bits/stdc++.h>
#define re register int
using namespace std;

int n,d,k,cnt,ans;  //cnt存当前连胜数，ans存答案 
string temp;  //边读边算，不用开数组 

int main()
{
	std::scanf("%d%d",&k,&n);  //读入不解释 
	for(re i=1;i<=n;i++)
	{
		std::cin>>temp;
	
		bool p=0;  //用于判断 
		for(re j=0;j<k;j++)
			if(temp[j]=='0')  //只要有一个为零，那说明人没来齐 
			{
				p=1;
				break;  //直接退出循环 
			}
		if(p==1)
			cnt++;  //增加连胜场数 
		else  //如果人来齐了 
		{
			if(cnt>ans)
				ans=cnt;  //更新答案 
			cnt=0;  //清零连胜 
		}
	}
	
	if(cnt>ans) ans=cnt;
	//这个地方要注意！！ 全部读完之后可能还会积累连胜场数，所以这里也要更新答案。 
	std::printf("%d",ans);  //输出不解释 
	return 0;
}
```

~~话说为毛人都来齐了他们就会赢啊？~~

---

## 作者：_Qer (赞：0)

这个n和d不按常理出牌啊QAQ，坑我半天

n是人数d是天数

用一个数组来存每天的结果，最后稍微算一下就好了

每天的结果就是当天所有数&的结果（全为1则结果为1，否则0）

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[110], c;//用数组换成bool/int也行
//a[i]表示第i天的结果
int main(void) {
    register int n, d, ans = 0, i, j, cnt;
    //n, d如题，ans为答案，i, j循环变量，cnt连胜天数
    cin >> n >> d;
    memset(a, 1, sizeof(a));//都初始化为1，否则结果一直会是0
    a[0] = 0;
    for (i = 1; i <= d; ++i) {//外循环是天数
        for (j = 1; j <= n; ++j) {//内循环是人数
            cin >> c;
            a[i] &= (c - '0');//按位与
        }
    }
    for (i = 1, cnt = 0; i <= d; ++i) {
        //cout << (int)a[i] << endl;
        a[i] == 0 ? ++cnt : cnt = 0, ans = max(ans, cnt);
        //()?():()；
        //第一个表达式为真时执行:前，否则执行:后
        //这里看起来我后半部分写错了（先cnt=0）
        //其实这里一句话是从后往前执行的（我也不知道为什么QAQ）
    }
    cout << max(ans, cnt) << endl;
    //这里的max必要，可能最后一天结果为1，没有更新ans
    return 0;
}
```

---

