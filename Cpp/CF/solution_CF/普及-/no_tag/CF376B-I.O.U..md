# I.O.U.

## 题目描述

Imagine that there is a group of three friends: A, B and С. A owes B 20 rubles and B owes C 20 rubles. The total sum of the debts is 40 rubles. You can see that the debts are not organized in a very optimal manner. Let's rearrange them like that: assume that A owes C 20 rubles and B doesn't owe anything to anybody. The debts still mean the same but the total sum of the debts now equals 20 rubles.

This task is a generalisation of a described example. Imagine that your group of friends has $ n $ people and you know the debts between the people. Optimize the given debts without changing their meaning. In other words, finally for each friend the difference between the total money he should give and the total money he should take must be the same. Print the minimum sum of all debts in the optimal rearrangement of the debts. See the notes to the test samples to better understand the problem.

## 说明/提示

In the first sample, you can assume that person number 1 owes 8 rubles to person number 2, 1 ruble to person number 3 and 1 ruble to person number 4. He doesn't owe anybody else anything. In the end, the total debt equals 10.

In the second sample, there are no debts.

In the third sample, you can annul all the debts.

## 样例 #1

### 输入

```
5 3
1 2 10
2 3 1
2 4 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4 3
1 2 1
2 3 1
3 1 1
```

### 输出

```
0
```

# 题解

## 作者：FQR_ (赞：9)

### 题目大意：

有 $ n $ 个人，已知每个人与人之间的债务，求债务总和。

### 思路

设置一个数组 $a$，表示每个人欠的钱。

每当输入债务时，将欠钱人的债务增加输入的钱数，将借钱人的债务减少这个钱数。

最后，把所有正数加起来，就得到了答案。

### AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[105];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		a[x]-=z;//借钱人的债务减少z
		a[y]+=z;//欠钱人的债务增加z
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(a[i]>0) ans+=a[i];//把钱没还清的人欠的钱加起来
	cout<<ans;
 	return 0;
}


```

---

## 作者：_Agave_ (赞：1)

[题目](https://www.luogu.com.cn/problem/CF376B)

这道题优化债务的方法就是用一个人可以收回的债去补这个人欠的债。

于是我们用一个 $a$ 数组去记录第 $i$ 个人欠债的情况，

欠债就减去对应的数值，否则加上对应的数值。

这样的话，欠的债和收回的债会自动抵消。

时间复杂度只有 $O(n)$ .

```cpp
#include <bits/stdc++.h>
#include <vector>
#include <string>
using namespace std;
int n,m,ans=0,a[10005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		a[x]-=z,a[y]+=z;//自动抵消
	}
	for(int i=1;i<=n;i++){
		if(a[i]>0) ans+=a[i];//如果是绝对值，一个债会被算两遍
	}
	printf("%d",ans);//输出答案
	return 0;
}

```


---

## 作者：翼德天尊 (赞：1)

## STEP 1 题目简述

有 $n$ 个人以及他们之间的 $m$ 个债务关系，如果 $A$ 欠 $B$ $m$ 元，$B$ 欠 $C$ $m$ 元，则 $A$ 欠 $C$ $m$ 元且 $B$ 不再有任何债务在身。

## STEP 2 浅谈做法

看到这道题的第一眼，其实我是想用图论做的，但是觉得有点麻烦，于是就没有开动。

经过一番思考，其实我们可以想到，如果 $A$ 欠 $B$ $m$ 元，则相当于 $B$ 如果欠别人的钱则可以少还 $m$ 元。

于是我们就可以想到用一个数组来表示每一个现在的钱，初始均为 $0$。然后每次欠款则相当于是借钱者少了 $m$ 元，给钱者多了 $m$ 元。最终输出所有正数或者负数的欠款额即可。

**代码如下：**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 105
int n,m,now[N];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}

int main(){
	n=read(),m=read();
	for (int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		now[y]+=z,now[x]-=z; 
	} 
	int ans=0;
	for (int i=1;i<=n;i++)
		if (now[i]>0) ans+=now[i];
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：pengzy (赞：0)

### 题意：

有 $n$ 个人和 $m$ 组债务关系，第 $i$ 组债务关系表示第 $a$ 人欠了第 $b$ 人 $c$ 元。要求你输出 **化简债务** 后的债务总和。

### 思路：

考虑用一个长度为 $n$ 的数组 $money$，$money_{i}$ 表示第 $i$ 个人现有的钱。如果欠钱，就减去欠的钱数；如果别人欠你钱，就加上欠的钱数。因为钱是流通的，自己一开始欠的钱可能会通过其他人欠他钱的方式使自己还清债务。但是，如果所有操作进行完以后还是无法还清债务，就需要统计一下答案。同时，这样能使债务流通，从而化简债务。

不懂欢迎回复。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
int n,m,money[1005],ans=0;
int main()
{
	n=read(),m=read();
	for(int i=1,a,b,c;i<=m;i++) {
		a=read(),b=read(),c=read();
		money[a]-=c;
		money[b]+=c;
	}
	for(int i=1;i<=n;i++)
		if(money[i]<0)ans+=abs(money[i]);//若他始终无法还清债务，则需要累计答案
	cout<<ans;
	return 0;
}
```

---

## 作者：Xdl_rp (赞：0)

~~这一道题评成蓝题就有点过了吧！这也就黄题的感觉！~~

进入正题：
------------

我们可以将每个人的钱数设为 $0$，如果 `a` 欠 `b` $\ n$ 元，就将 $money_a - n$ 且 $money_b + n$，最后将所有的债务用绝对值计算，这样就完成了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int g = 0, f = 1;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) g = (g << 1) + (g << 3) + (c ^ 48), c = getchar();
	return g * f;
}
void write(int x) {
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int mon[1005];
signed main() {
	int n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		int x = read(), y = read(), num = read();
		mon[x] -= num;//x的钱数减去n
		mon[y] += num;//y的钱数加上n
	}
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += abs(mon[i]);//把每个人的钱用绝对值加起来
	write(sum / 2);//除以2就是答案了
	return 0;
}
```


---

## 作者：wzm2007 (赞：0)

# 将所有欠债的人减去债务额，反之加上债务额
# 再把所有正数相加
# 代码如下：
	#include<bits/stdc++.h>  
	using namespace std;  
	int a[110];  
	int main()  
	{
		int n,m,ans=0;
		cin>>n>>m;
		for(int i=0;i<m;i++)
		{
			int x,y,z;
			cin>>x>>y>>z;
			a[y]+=z;
			a[x]-=z;
		}
		for(int i=1;i<=n;i++)
			if(a[i]>0)ans+=a[i];
		cout<<ans;
		return 0;  
	}

---

## 作者：Y_inG (赞：0)

教练那个混蛋居然搬原题考我们。。。。

~~（虽然我还是0爆了）~~

表达一下我悲痛的心情
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;
const int max_n=1e6+10;
const int max_m=1e6+10;
int a[max_n];
inline int getnum()
{
	int ans=0;
	bool flag=false;
	char c;
	while((c=getchar())==' '||c=='\n' ||c=='\r');
	if(c=='-')
		flag=true;
	else
		ans=c -'0';
	while(isdigit(c=getchar()))
		ans=ans*10+c-'0';
	return ans;
}//读入优化（我们考试评测这道题没说要优化=-=，结果一把80分）虽然不知道这里要不要。。。。。。。
int main()
{
//	freopen("debt.in","r",stdin);
//	freopen("debt.out","w",stdout);//这个是文件输入和输出
	int n=getnum();
	int m=getnum();
	for(int i=1;i<=m;i++)
	{
		int aa,bb,c;
		aa=getnum();
		bb=getnum();
		c=getnum();
		a[aa]+=c;
		a[bb]-=c;//欠别人的和被人欠的相抵消
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(a[i]>0)
			ans += a[i];//还有剩就加起来
	cout<<ans;
}
```
~~我tm那个时候居然打错了。。。~~

---

## 作者：diqiuyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF376B)

好水啊。

**思路**

其实吧，这题的思路很简单，只要把每个人的财产都算出来就行了。当有人欠他钱时财产就增加，他欠别人钱时财产就减少，最后统计所有欠的钱的总和即可。之所以可以这样做，是因为我们可以假设有一个银行作为中转商，当有人需要还钱时，不妨令其向银行借钱。如此一来，每个人都不会欠人钱了。而最后如果还有无法通过别人的还钱还清向银行借的钱的人，就只能让债务总额加上这一笔钱了。

**CODE**
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int read(int x=0,bool f=1){
	char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}
	return f?x:-x;
}
int n,m,val[105],x,y,z,ans;//val 存每个人的钱数
int main(){
	n=read(),m=read();
	while(m--){
		x=read(),y=read(),z=read();
		val[x]-=z;
		val[y]+=z;
	}
	for(int i=1;i<=n;i++)
		ans+=max(0,val[i]);
        //其实由于财产总和为 0，不算亏的算赚的也可以
	printf("%d\n",ans);
	return 0;
}

```

~~话说这题应该用图论也可以，就是作者太菜了不会写罢了。~~

---

