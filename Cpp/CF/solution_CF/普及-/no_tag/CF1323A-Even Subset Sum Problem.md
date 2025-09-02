# Even Subset Sum Problem

## 题目描述

### 题意简述

给定数组 $a$，求出它一个和为偶数的的非空子集。

## 说明/提示

$1 \leq t,n,a_i \leq 100$。

翻译 by Meatherm

## 样例 #1

### 输入

```
3
3
1 4 3
1
15
2
3 5```

### 输出

```
1
2
-1
2
1 2```

# 题解

## 作者：do_while_false (赞：4)

题目大意:

给定一个集合，选择这个集合的一个非空子集，使得这个非空子集元素之和为偶数。

输入输出:

输入共 $t$ 组数据，每组数据有一个整数 $n$ ，和长度为 $n$ 的序列 $a_1,a_2,a_3...a_n$ 。

每组输入对应一个输出，若无这样的非空子集，则输出 $-1$ 。否则第一行输出一个整数 $k$ ，表示这个非空子集内元素的个数，第二行输出这个非空子集内元素在原集合中的位置。(如果有多个子集成立，随便输出一个)

题目分析:

既然要使这个非空子集内元素之和为偶，则所选的数必定是偶数个奇数或任意个偶数，或者是它们之和。

但是此题只让输出其中一个子集，我们就来简化一下:

- 如果集合内有正整数个偶数，则必然有一个偶数。所以使非空子集的元素个数为一，唯一元素为这个偶数就行了。

- 如果集合内有偶数个奇数，则必然有两个奇数。则使非空子集的元素个数为二，其中两个元素为原集合内的两个奇数即可。

代码如下:

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];
int t,i,n,pre,now,flag;//记录两个奇数,pre记录第一次出现位置,now记录第二次出现位置
inline int read() {
	int r=0;bool flag=true;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=false;ch=getchar();}
	while(ch>='0'&&ch<='9'){r=(r<<3)+(r<<1)+(ch^48);ch=getchar();}
	return flag==true?r:~r+1;
}
inline void write(int x) {
	char ch[20];int len=0;
	if(x<0){putchar(45);x=~x+1;}
	do{ch[len++]=x%10+48;x/=10;}while(x>0);
	for(int i=len-1;i>=0;i--) putchar(ch[i]);
	putchar('\n');
}
int main(){
	t=read();
	while(t--){
		flag=pre=0;
		n=read();
		for(i=1;i<=n;i++) a[i]=read();
		for(i=1;i<=n;i++) {
			if(a[i]%2==0) {
				write(1);write(i);
				flag=1;
				break;
			}
			else if(!pre) pre=i;//pre记录第一次奇数出现位置
			else {
				now=i;//now记录第二次出现奇数位置
				flag=1;
				write(2);
				printf("%d %d/n",pre,now);
				break;
			}
		}
		if(flag==0) printf("-1\n");
	}
	return 0;
}
```

如果CE了不要怪我。

管理员大大求过,qwq。

---

## 作者：CBW2007 (赞：1)

在我的博客食用效果更佳！<https://www.cbw2007.tk/articles/CF-626-div2-A-sol/>

Codeforces Round #626 (Div. 2) A题【Even Subset Sum Problem】题解

> 原题链接：[Problem - 1323A - Codeforces](https://codeforces.com/problemset/problem/1323/A)或[CF1323A Even Subset Sum Problem - 洛谷 | 计算机科学教育新生态](https://www.luogu.com.cn/problem/CF1323A)

这题还是很水的，跟着题意模拟就行了，但是我在review其他大佬的代码时，发现了一种稍微不一样的思路：

1. 判断数组中有无偶数，有的话就他一个人构成一个子集
2. 如果没有偶数，且数组中只有一个数（此时必为奇数），那么就他一个奇数，怎么也构不成偶数
3. 如果数组由两个及以上的纯奇数组成，**那么随便取两个就好啦**，因为这时数组里只有奇数，奇数+奇数=偶数，为了方便，就固定取前两个

核心代码：

```cpp
int n;
cin>>n;
bool flag=false;
for (int i=1;i<=n;i++)
{
	int ai;
	cin>>ai;
	if (ai%2==0&&!flag)//如果有偶数
	{
		cout<<1<<endl;//当前这个就行了
		cout<<i<<endl;
		flag=true;//标记一下，避免重复
	}
}
if (flag)//避免重复
	continue;
if (n<=1)//无解情况
	cout<<-1<<endl;
else
{
	cout<<2<<endl;//前两个之和必为偶数
	cout<<1<<" "<<2<<endl;
}
```



---

## 作者：Transparent (赞：1)

### 题意：

给你一个包含 $n$ 个数的数组，
找出它的一个非空子集，
使这个子集中所有元素的和为偶数。
如果不存在这样的一个子集，就输出 $-1$ 。
一个测试点包含多组数据，
第一行输入 $t$ 表示数据组数。

### 方法：

暴力枚举每一个可能的子集，找到符合条件的就直接输出。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[101];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(register int i=1;i<=n;i++)
		{
			scanf("%d",a+i);
		}
		int sum=0;
		bool f=0;
		for(register int i=1;i<=n;i++)//区间首
		{
			sum=0;//当前区间的和
			for(register int j=i;j<=n;j++)//区间尾
			{
				sum+=a[j];
				if(sum%2==0)//找到答案
				{
					printf("%d\n",j-i+1);
					for(register int k=i;k<j;k++)//依次输出编号
					{
						printf("%d ",k);
					}
					printf("%d\n",j);
					f=1;//标记并退出循环
					break;
				}
			}
			if(f)
			break;
		}
		if(!f)//没有找到输出-1
		{
			printf("-1\n");
		}
	}
  	return 0;
}
```


---

## 作者：dead_X (赞：0)

## 1 题意简述
翻译已经提交，所以咕咕了
## 2 思路简述
考虑到如果能构造出一个长度大于2的序列，这个序列中必然有两个奇偶性相同的项，删去这两个之后序列仍满足性质。

所以如果存在解，必定有一个解为长度为 $1$ 或 $2$ 的序列。

长度为 $1$ 时为一个偶数

长度为 $2$ 时为两个奇数或两个偶数。

所以找到一个偶数或者两个奇数后输出，找不到的时候输出 ``-1``。
## 3 代码
```
#include<bits/stdc++.h>
using namespace std;
int a[1003];
int _main()
{
	int n;
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	bool f=0; int k;
	for(int i=1; i<=n; i++) if(a[i]%2) if(f) return printf("2\n%d %d\n",k,i); else f=1,k=i; else return printf("1\n%d\n",i);
	return printf("-1\n");
	//qwq
}
int main()
{
	int t;
	cin>>t;
	while(t--) _main();
}
```
## 4 评价
赛时想出做法所用时间:0min

比赛A掉所用时间:7min

建议难度:红/橙

---

## 作者：Meatherm (赞：0)

比较友善的 Div.2 A。

题目只要求是原数组的非空子集，没有对选的个数做限制。

若原数组存在偶数，则随便选个偶数就行了。

若原数组存在两个及以上奇数，则选任意两个奇数，它们的和一定是偶数。

其实代码稍稍有点长。因为当 $n>1$ 的时候是一定有解的，我有点 naive 了，大家凑合着看看吧。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=100010,INF=0x3f3f3f3f;
int a[N];
int T;
int ca,cb;
int n;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
int main(void){
	T=read();
	while(T--){
		n=read();
		ca=cb=0;
		for(rr int i=1;i<=n;++i){
			a[i]=read();
			if(a[i]%2){
				++ca;
			}else{
				++cb;
			}
		}
		if(cb){
			printf("%d\n",1);
			for(rr int i=1;i<=n;++i){
				if(a[i]%2==0){
					printf("%d\n",i);
					break;
				}
			}
			goto End;
		}else if(ca>1){
			int cnt=0;
			printf("%d\n",2);
			for(rr int i=1;i<=n;++i){
				if(a[i]%2==1){
					printf("%d ",i);
					++cnt;
				}
				if(cnt==2){
					break;
				}
			}
		}else{
			puts("-1");
		}
		End:;
	}

	return 0;
}

```

---

## 作者：do_while_true (赞：0)

### 题目翻译

给定一个集合(集合内元素可以重复)，输出这个集合的一个非空子集，这个非空子集的元素和必须是偶数

#### 输入格式

第一行一个整数 $t$ 表示一共有多少组数据

对于每一组数据 :

第一行一个整数 $n$ 表示一共有多少个元素

第二行 $n$ 个整数 分别表示每一个元素

#### 输出格式

$t$组输出，对于每一组输出

若不存在这种非空集合，输出 -1

若存在，第一行一个整数$k_i$ 表示子集的大小

第二行$k_i$个整数 表示子集的每一个元素

### 题目分析

题目还是很好理解的，首先明白一个性质 : 任意偶数相加的和仍为偶数，偶数(不为0)个奇数相加和也是偶数

所以如果给定的集合中有偶数，就输出其中一个偶数就可以

如果没有偶数，只需要输出两个奇数就可以(两个奇数的和一定为偶数)

### *Code:*
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,a[101];
int ji[3],cnt,fl;
//ji[1]和ji[2]表示两个奇数，cnt表示现在一共找到了几个奇数
//fl为1时有解，fl为0时无解
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		cnt=fl=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
		{
			if(a[i]%2==0){//如果有一个偶数，直接输出这一个偶数就可以
				printf("1\n%d\n",i);
				fl=1;
				break;
			}
			if(a[i]%2==1){//如果是奇数
				ji[++cnt]=i;//存入这个奇数
				if(cnt==2){//如果到目前有2个奇数了
					printf("2\n%d %d\n",ji[1],ji[2]);//输出这两个奇数
					fl=1;
					break;
				}
			}
		}
		if(!fl) printf("-1\n");//如果fl没被标记，说明无解
	}
	return 0;
}
```


---

