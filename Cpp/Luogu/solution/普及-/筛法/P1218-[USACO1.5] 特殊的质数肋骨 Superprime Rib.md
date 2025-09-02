# [USACO1.5] 特殊的质数肋骨 Superprime Rib

## 题目描述

农民约翰的母牛总是产生最好的肋骨。你能通过农民约翰和美国农业部标记在每根肋骨上的数字认出它们。 

农民约翰确定他卖给买方的是真正的质数肋骨，是因为从右边开始切下肋骨，每次还剩下的肋骨上的数字都组成一个质数。  

举例来说：$7\ 3\ 3\ 1$ 全部肋骨上的数字 $7331$ 是质数；三根肋骨 $733$ 是质数；二根肋骨 $73$ 是质数；当然,最后一根肋骨 $7$ 也是质数。$7331$ 被叫做长度 $4$ 的特殊质数。  

写一个程序对给定的肋骨的数目 $n$，求出所有的特殊质数。$1$ 不是质数。

## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 8$。

题目翻译来自NOCOW。

USACO Training Section 1.5


## 样例 #1

### 输入

```
4
```

### 输出

```
2333
2339
2393
2399
2939
3119
3137
3733
3739
3793
3797
5939
7193
7331
7333
7393
```

# 题解

## 作者：zybnxy (赞：180)

## 重要的事情说三遍

# 此解绝对不是正解！
# 此解绝对不是正解！！
# **此解绝对不是正解！！！**

好了，其实这道题暴力就可以过。
怎么个暴力法。。。。 
# 八重循环！！！

我们开一个$N$重循环，检测一共的$N-1$个数是不是素数，如果是，则输出

然而，这种做法肯定会超时。所以我们需要优化

* 优化一，我们可以肯定，第一位肯定是2,3,5,7。不然它不可能是素数

  我们可以开一个数组$A[4]$，分别存储$2,3,5,7$。

* 优化二，第$2$位到第$ N-1$位中，每一位都必须是奇数，不然也满足不了素数的调节
  我们开一个数组$b[5]$，分别存储$1,3,5,7,9$。

## 以下高能！
## 以下高能！！
## 以下高能！！！
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
#include<set>
#include<list>
#include<stack>
#include<vector>
#include<cstdlib>
#include<iterator>
#include<deque>
#include<ctime>
#include<iomanip>
#include<map>
#include<bitset>
#include<utility>
#include<sstream>
using namespace std;
bool prime(int n)
{
    if(n==1)return false;
    for(int i=2;i*i<=n;i++)
    {
    	if(n%i==0)return false;
    }
    return true;
}
inline void write(int x)
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
    
}
int a[5]={0,2,3,5,7};
int b[6]={0,1,3,5,7,9};
int main()
{
	int n,i,j,k,q,w,e,r,t;
	scanf("%d",&n);
	if(n==1)
		for(i=1;i<=4;i++)
			if(prime(a[i]))
				{write(a[i]);putchar('\n');}
	if(n==2)
		for(i=1;i<=4;i++)
			for(j=1;j<=5;j++)
				if(prime(a[i]*10+b[j]))
					{write(a[i]*10+b[j]);putchar('\n');}
	if(n==3)
		for(i=1;i<=4;i++)
			for(j=1;j<=5;j++)
				for(k=1;k<=5;k++)
					if(prime(a[i]*100+b[j]*10+b[k])&&prime(a[i]*10+b[j])&&prime(a[i]))
						{write(a[i]*100+b[j]*10+b[k]);putchar('\n');}
	if(n==4)
		for(i=1;i<=4;i++)
				for(j=1;j<=5;j++)
					for(k=1;k<=5;k++)
						for(q=1;q<=5;q++)
							if(prime(a[i]*1000+b[j]*100+b[k]*10+b[q])&&prime(a[i]*100+b[j]*10+b[k])&&prime(a[i]*10+b[j])&&prime(a[i]))
								{write(a[i]*1000+b[j]*100+b[k]*10+b[q]);putchar('\n');}
	if(n==5)
		for(i=1;i<=4;i++)
			for(j=1;j<=5;j++)
				for(k=1;k<=5;k++)
					for(q=1;q<=5;q++)
						for(w=1;w<=5;w++)
							if(prime(a[i]*10000+b[j]*1000+b[k]*100+b[q]*10+b[w])&&prime(a[i]*1000+b[j]*100+b[k]*10+b[q])&&prime(a[i]*100+b[j]*10+b[k])&&prime(a[i]*10+b[j])&&prime(a[i]))
								{write(a[i]*10000+b[j]*1000+b[k]*100+b[q]*10+b[w]);putchar('\n');}
	if(n==6)
		for(i=1;i<=4;i++)
			for(j=1;j<=5;j++)
				for(k=1;k<=5;k++)
					for(q=1;q<=5;q++)
						for(w=1;w<=5;w++)
							for(e=1;e<=5;e++)
								if(prime(a[i]*100000+b[j]*10000+b[k]*1000+b[q]*100+b[w]*10+b[e])&&prime(a[i]*10000+b[j]*1000+b[k]*100+b[q]*10+b[w])&&prime(a[i]*1000+b[j]*100+b[k]*10+b[q])&&prime(a[i]*100+b[j]*10+b[k])&&prime(a[i]*10+b[j])&&prime(a[i]))
									{write(a[i]*100000+b[j]*10000+b[k]*1000+b[q]*100+b[w]*10+b[e]);putchar('\n');}
	if(n==7)
		for(i=1;i<=4;i++)
			for(j=1;j<=5;j++)
				for(k=1;k<=5;k++)
					for(q=1;q<=5;q++)
						for(w=1;w<=5;w++)
							for(e=1;e<=5;e++)
								for(r=1;r<=5;r++)
									if(prime(a[i]*1000000+b[j]*100000+b[k]*10000+b[q]*1000+b[w]*100+b[e]*10+b[r])&&prime(a[i]*100000+b[j]*10000+b[k]*1000+b[q]*100+b[w]*10+b[e])&&prime(a[i]*10000+b[j]*1000+b[k]*100+b[q]*10+b[w])&&prime(a[i]*1000+b[j]*100+b[k]*10+b[q])&&prime(a[i]*100+b[j]*10+b[k])&&prime(a[i]*10+b[j])&&prime(a[i]))
										{write(a[i]*1000000+b[j]*100000+b[k]*10000+b[q]*1000+b[w]*100+b[e]*10+b[r]);putchar('\n');}
	if(n==8)
		for(i=1;i<=4;i++)
			for(j=1;j<=5;j++)
				for(k=1;k<=5;k++)
					for(q=1;q<=5;q++)
						for(w=1;w<=5;w++)
							for(e=1;e<=5;e++)
								for(r=1;r<=5;r++)
									for(t=1;t<=5;t++)
										if(prime(a[i]*10000000+b[j]*1000000+b[k]*100000+b[q]*10000+b[w]*1000+b[e]*100+b[r]*10+b[t])&&prime(a[i]*1000000+b[j]*100000+b[k]*10000+b[q]*1000+b[w]*100+b[e]*10+b[r])&&prime(a[i]*100000+b[j]*10000+b[k]*1000+b[q]*100+b[w]*10+b[e])&&prime(a[i]*10000+b[j]*1000+b[k]*100+b[q]*10+b[w])&&prime(a[i]*1000+b[j]*100+b[k]*10+b[q])&&prime(a[i]*100+b[j]*10+b[k])&&prime(a[i]*10+b[j])&&prime(a[i]))
											{write(a[i]*10000000+b[j]*1000000+b[k]*100000+b[q]*10000+b[w]*1000+b[e]*100+b[r]*10+b[t]);putchar('\n');}
	return 0;
}


```


---

## 作者：HeZhenting (赞：95)

### 绝对是好方法
### 用队列，易懂且简便
ps:肯定要发挥STL的优势嘛！！！

# 不废话，上题解！！！

```cpp
#include<bits/stdc++.h>
using namespace std;

bool isprime(int x) {
	if (x%2==0) return false;
	int m=sqrt(x);
	for(int i=3;i<=m;i+=2)
	if (x%i==0) return false;
	return true;
}

int main() {
	queue <int> q;
	int n,m=4,a[]={2,3,5,7},b[]={1,3,7,9};
	scanf("%d",&n);
	for(int i=0;i<4;i++) q.push(a[i]);
	for(int i=2;i<=n;i++) {
		int l=m;
		m=0;
		for(int j=0;j<l;j++) {
		    for(int k=0;k<4;k++)
			if (isprime(q.front()*10+b[k]))    q.push(q.front()*10+b[k]),m++;
			q.pop();
		}
	}
	while(!q.empty()) {
		printf("%d\n",q.front());
		q.pop();
	}
	return 0;
}
```
### 咳咳，说正经的！

原理：保证每次放入队列里的都是质数，从一位数到n位数拼数字查找，再把队头上一次放入的删掉，剩下的就全是答案了！
###### （自认为算法极快）

小犇犇别忘了点赞哦！！！^_^

---

## 作者：安笙凉城 (赞：51)

#大水题


##说一下思路，用DFS，边加数字边判断，位数凑够了输出


###希望能对各位牛牛们有帮助


**贴代码**







```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5]={1,3,5,7,9};//枚举非首位的质数
bool prime(int x)//判断是否为质数
{
    if(x==1) return 0;//1不是质数
    if(x==2) return 1;//如果是2直接返回1
    for(int i=2;i<=sqrt(x);i++)//此处是一个优化，只需要循环到x的算术平方根即可，否则会超时
          if(x%i==0)
            return 0;//如果有除了1和他本身以外的因数不是质数
        return 1;//是质数返回1
}
void DFS(int k,int sum)//深搜代码，sum代表当前位数
{
    int p; 
    if(sum==n)//位数够了就输出
      {
          cout<<k<<endl;
          return;
      }
    else
      {
          for(int i=0;i<5;i++)
            {
            p=k*10+a[i];//在最后加数字
            if(prime(p))//如果已经不是质数就没有搜下去的必要了
              DFS(p,sum+1);//位数增加继续搜
          }
      }
}
int main()
{
    cin>>n;//输入位数
    DFS(2,1);
    DFS(3,1);
    DFS(5,1);
    DFS(7,1);//首位数字只能为2，3，5，7，所以直接从他们开始搜
    return 0;
}
```

---

## 作者：hensier (赞：19)

UPD 2022.8.22 重新撰写代码并修改措辞。

这是一道搜索的基础练习题，BFS 和 DFS 都可以解决。

不妨考虑一下特殊质数的性质——它从头开始截取任意个数位顺次得到的整数都是质数。

不难发现，这种特殊质数的第一位必定是 $2,3,5,7$ 中的其中一个（因为这一位必须是质数，且一位数质数只有 $2,3,5,7$）。因此，可以分别以这四个一位数为基础，每次在末尾添加一位，就能得到一个新的整数。这样，我们就能覆盖到所有范围内的整数，再找出所有的质数输出即可。

细节优化：向数末尾添加的数位只能是 $1,3,7,9$，因为不难证明任何一个以 $2,4,5,6,8,0$ 结尾的不少于两位的整数必为合数。

BFS 代码：

```cpp
#include<bits/stdc++.h>
int n,q[101]={0,2,3,5,7};
const int m[4]={1,3,7,9};
bool check(int x)
{
    if(x<2)return false;
    for(int i=2;i*i<=x;++i) // 如果 x 有一个因数 i，则 x/i 必然也是 x 的一个因数，因此只需枚举到 x 的平方根即可
        if(x%i==0)
            return false;
    return true;
}
int main()
{
    scanf("%d",&n);
    for(int front=1,rear=4,l=int(pow(10,n-1)),r=int(pow(10,n));front<=rear;++front)
    {
        if(q[front]>r)break;
        if(q[front]>l)printf("%d\n",q[front]);
        // 因为是按照从小到大进行遍历的，所以位数相同的质数在队列中必然有序，下面的 DFS 同理
        for(int i=0;i<4;++i)
        {
            int x=q[front]*10+m[i];
            if(check(x))q[++rear]=x;
        }
    }
    return 0;
}
```

DFS 代码：

```cpp
#include<bits/stdc++.h>
int n,l,r,cnt,ans[101];
const int s[4]={2,3,5,7},m[4]={1,3,7,9};
bool check(int x)
{
    if(x<2)return false;
    for(int i=2;i*i<=x;++i)
        if(x%i==0)
            return false;
    return true;
}
void dfs(int x)
{
    if(x>r||!check(x))return;
    if(x>l)ans[++cnt]=x;
    for(int i=0;i<4;++i)dfs(x*10+m[i]);
}
int main()
{
    scanf("%d",&n);
    l=int(pow(10,n-1)),r=int(pow(10,n));
    for(int i=0;i<4;++i)dfs(s[i]);
    for(int i=1;i<=cnt;++i)printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Last_Reincarnation (赞：15)

######  蒟蒻的代码很详细，很容易懂

很明显这是一道关于线性筛的~~大水~~题
思路：线性筛
首先读入n，处理要把素数筛到几，以下代码处理，m是要筛到的数
```c
while(n){
		m*=10;
		n--;
	}

```

然后就是关键的欧拉筛，如果不会请转到P3383线性筛素数

然后求一下二分答案，求一下大于等于m/10的第一个位置
（为了节省时间~~但貌似没毛用~~）

举个例子，加入输入的n为4，则需要找的范围为1000到10000

最后从m/10开始，到prime个数cnt

在for循环中，flag是个标记，初始为0，如果flag在while循环后还是0，则满足题目条件，输出即可；若在循环中不满足，则flag会变成1，则不满足条件
```c
for(int j=qwq;j<=cnt;j++){
			flag=0;
			op=prime[j];
			while(op){
				op/=10;
				if(v[op]){flag=1;break;}
			}
			if(!flag)printf("%d\n",prime[j]);
		}

```
然后你会发现即使你写了二分，想了好多方法优化，但最后一个坑爹的点还是tle，然后使出最后的办法，手动开一下O2，给评测机吸氧（正规比赛一定不要用O2，会有各种未知错误出现）
```c
#pragma GCC optimize(2)

```
最后完美AC
祝大家AK~~吊打~~noip

如果还有不懂，请在评论区评论，为noip的本蒟蒻正在天天刷题，一定会解答的


```c
#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=99999999;
const int maxx=1000000010;
int n,m=1,prime[maxn],cnt,flag,op,qwq;
bool v[maxx];
int houji(int x,int y){
	while(x<y){
		int mid=(x+y)>>1;
		if(prime[mid]>=n)y=mid;
		else x=mid+1;
	}
	return x;
}
int main(){
	scanf("%d",&n);
	while(n){
		m*=10;
		n--;
	}
	n=m/10;
	v[1]=1;v[0]=0;
	for(int i=1;i<=m;i++){
		if(!v[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&i*prime[j]<=m;j++){
			v[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	qwq=houji(1,cnt);
	for(int j=qwq;j<=cnt;j++){
			flag=0;
			op=prime[j];
			while(op){
				op/=10;
				if(v[op]){flag=1;break;}
			}
			if(!flag)printf("%d\n",prime[j]);
		}
	return 0;
}

```


---

## 作者：LJC00118 (赞：6)

# P1218题解


## 这道题用搜索，一位一位加，一旦发现不是素数就剪枝


### 例子：2->21(剪枝)，2->23(输出)，2->27(剪枝)，2->29(输出)


### 我们得出了规律：在末尾只能添加1,3,7,9四个数


### 如果添加5则会变成5的倍数


### 下面是代码实现


```cpp
#include<bits/stdc++.h>//传说中的万能头文件
using namespace std;
int n;
bool pd(int x)//最基础的判断素数
{
    if(x==2) return 1;
    if(x%2==0) return 0;
    for(int i=3;i*i<=x;i+=2)
    {
        if(x%i==0) return 0;
    }
    return 1;
}
void dfs(int u,int x)//搜索开始了
{
    if(u>n)//搜出了答案
    {
        printf("%d\n",x);//输出
        return;//结束本次搜索
    } 
    int tmp=x*10+1;//添加1
    if(pd(tmp)) dfs(u+1,tmp);//如果是素数就继续搜索，不然剪枝
    tmp=x*10+3;//添加3
    if(pd(tmp)) dfs(u+1,tmp);
    tmp=x*10+7;//添加7
    if(pd(tmp)) dfs(u+1,tmp);
    tmp=x*10+9;//添加9
    if(pd(tmp)) dfs(u+1,tmp);
    return;//结束本次搜索
}
int main()
{
    scanf("%d",&n);
    dfs(2,2);//首位为2
    dfs(2,3);//首位为3
    dfs(2,5);//首位为5
    dfs(2,7);//首位为7
    return 0;//简洁的主程序
}
```

---

## 作者：AutumnKite (赞：6)

用递推算法，a[i,j]表示i位的第j个特殊质数。可以想到，第1位一定是质数，所以是2,3,5,7之一，后面的一定是1,3,7,9之一，因为除了2的质数都是奇数，并且如果有5的话就能被5整除。可以得到如下程序段：（用a[i,0]表示i位的特殊质数的个数）

```cpp
  a[1,0]:=4; a[1,1]:=2; a[1,2]:=3; a[1,3]:=5; a[1,4]:=7;
  for i:=2 to n do 
    for j:=1 to a[i-1,0] do 
      for k:=1 to 4 do 
        begin
          x:=a[i-1,j]*10+p[k];
          if prime(x) then //只需判断当前新数是否为质数就行了，因为前面的一定满足特殊质数要求
            begin
              inc(a[i,0]);
              a[i,a[i,0]]:=x;
            end;
        end;
```
判断素数时能加上一个简单有效的优化
trunc(sqrt(x))

所以判断素数程序段如下：

```cpp
function prime(x:longint):boolean;
var
  i:longint;
begin
  if x<2 then exit(false);
  for i:=2 to trunc(sqrt(x)) do 
    if x mod i=0 then exit(false);
  exit(true);
end;
```

---

## 作者：雪颜 (赞：5)

首先，我们看到这题，第一个想法一定是枚举，然而这并不现实，所以我们想到枚举每一位，来构造质数。于是我们可以想到搜索。然后我们知道，只有开头能够出现2，5，其它数位不可能是偶数和5，所以枚举每一位数字的时候自然想到剪枝手段：跳过2,4,5,6,8.此外，另一个剪枝就是生成的数是否是质数，可以写个判断函数。代码如下。

```cpp
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
bool pri(int x){
    if(x==2) return true;
    if(x<2||x%2==0) return false;
    for(int tmp=3;tmp*tmp<=x;tmp+=2){
        if(x%tmp==0) return false;
    }
    return true;
}
void DFS(int last,int w){
    if(w==n){
        printf("%d\n",last);return;//找到符合条件的质数，直接输出
    }
    for(int i=1;i<=9;i+=2){//枚举当前位
        if(i==5) continue;
        if(pri(last*10+i)){
            DFS(last*10+i,w+1);
        }
    }
}
int main(){
    scanf("%d",&n);
    DFS(2,1);DFS(3,1);DFS(5,1);DFS(7,1);
    return 0;
}

```

---

## 作者：Lynx (赞：4)

这题，真，搜索。

讲真，一位一位地搜就可以啦（并不用剪枝），我用了0ms。

附代码


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
bool pd(int x)
{
    if(x==1)
        return 0;
    for(int i=2;i*i<=x;i++)
        if(x%i==0)
            return 0;
    return 1;
}
void dfs(int u,int fa)
{
    for(int i=1;i<=9;i++)
        if(pd(fa*10+i))
        {
            if(u==n)
                printf("%d\n",fa*10+i);
            else
                dfs(u+1,fa*10+i);
        }
}
int main()
{
    scanf("%d",&n);
    dfs(1,0);
    return 0;
}
```

---

## 作者：lzk5627 (赞：4)

这里先来一个暴力枚举法
首先，如果单单是枚举，是一定会超时的，所以我想出了一些优化方案
```c
#include<bits/stdc++.h>
using namespace std;
long long mmp(int x)//判断是否为质数
{
    if(x==2)//为2直接返回0
        return 0;
    if(x%2==0||x==1)//特判1
        return 1;
    for(int i=3;i*i<=x;i=i+2)//第一个优化，除二本身外，他的倍数都是合数，所以i每次+2；
        if(x%i==0)
            return 1;
    return 0;
}
int main()
{
    long long n;
    cin>>n;
    if(n==1)
        {
        cout<<2<<endl<<3<<endl<<5<<endl<<7<<endl;
        return 0;
        }
    for(int i=2*pow(10,n-1)+1;i<=8*pow(10,n-1)-1;i=i+2)//第二个优化，因为1,8，9，不是合数，所以以他们开头的数一定不合要求，减小了枚举范围
        {
        if((i+1)%6==0||(i-1)%6==0)//第三个优化，忘记从哪看到的规律，5以上的质数都与6相邻，减少判断质数的计算量
            {
            int k=n-1;
            while(k>=0)
                {
                if(mmp(floor(i/pow(10,k)))==0)//注意！！一定要从开头判断，因为开头数小容易判断，而且后面将会有巨大作用；
                    k--;
                else
                    break;
                }
            if(k==-1)
                cout<<i<<endl;//如果是，就输出
            else
            	{
            	if(k!=0)
            		i=(floor(i/pow(10,k))+1)*pow(10,k)-1;//最重要的优化，如果不是，就把不是质数的部分加1，这样可以跳过很多数
                }
            }
        }
    return 0;//完美结束
} 
```

---

## 作者：封禁用户 (赞：3)

本题按题意搜索模拟即可

很多人深搜都用2个元素其实只要一个元素就够了。

代码很简洁，题解最正常。

```cpp
#include<bits/stdc++.h>     //万能头文件。
using namespace std;
int a[1000],n;                       //n用来输入。a[]在当前深搜里面用来记录当前数字。
bool pd(int x){
    int k=sqrt(x);
    if(x==1)return 0;
    else if(x==2||x==3)return 1;
    else for(int i=2;i<=k;i++)
    if((x%i)==0) return 0;
    return 1;
}                                         //判断素数。
void dfs(int step){               //表示step搜到第几位数字。
    if(step==n){
        cout<<a[step]<<endl;
        return ;
}                                         //如果搜到了第n位数的话那么就输出。并且返回。 
      for(int i=1;i<=9;i++)     //枚举每一位数上的数字。
       if(pd(10*a[step]+i)){
           a[step+1]=10*a[step]+i;
           dfs(step+1);             //按照题意来深搜模拟。
        }
   } 
int main(){
    cin>>n;
    dfs(0);                            //我们从第零位数开始搜。 
    return 零;
}                                        //结束。
```

---

## 作者：dsjkafdsaf (赞：3)

# 暴力枚举大法！！！
其实看到楼下各位dalao用的都是搜索（好像吧）这题也可以用枚举过。。。

其实本题的思路是先输入质数，在在结尾加上数字，
符合条件再次执行，直至满足位数为止。

二话不说，先贴代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool zz(int h) {//这个函数是判断质数的...
	for(int i=2; i<=sqrt(h); i++) {
		if(h%i==0)return false;
	}
	return true;
}
int zs(int i,int n) {//关键主函数...
//i是可用数，n是答案所需的位数..
	int k=i,m1=0,y;//用k储存i的值备用
	while(k>0) {//计算当前位数
		k/=10;
		m1++;
	}
	if(m1!=(n-1)) for(int j=1; j<=9; j+=2) {
			y=i*10+j;
			if(zz(y)==true)zs(y,n);
		}
 //若不满足条件，在结尾加上奇数判断是否可用，若可用继续操作。
	if(m1==(n-1)) for(int j=1; j<=9; j+=2) {
			y=i*10+j;
			if(zz(y)==true)cout<<y<<endl;
  //若满足条件，输出。
		}
}
int main() {
	int n;
	cin>>n;//输入
	for(int i=2; i<=7; i++)if(zz(i)==true)zs(i,n);
	return 0;
}
```

---

## 作者：C20212724杨京朝 (赞：3)

搜索（回溯） + 筛法 + 打表
------------
备注：这是一篇集大成的题解

-----------
筛法：123ms

      #include <cmath>
      #include <iostream>
      #include <cstdio>
      using namespace std;
      int prime[100000005];
      bool vis[10000005],f;
      int cnt,n,m; 
      void Euler() { //线性筛模板不解释
          for(int i = 2;i <= m;i ++) {
              if(!vis[i]) prime[++ cnt] = i;
              for(int j = 1;j <= cnt && i * prime[j] <= m;j ++) {
                  vis[i * prime[j]] = 1;
                  if(i % prime[j] == 0) break;
              }
          }
      }
      int main() {
          scanf("%d",&n);
          m = pow(10,n);
          if(n == 8) {//打个表提高速度
              cout << "23399339" << endl << "29399999" << endl << "37337999" << endl << "59393339" << endl << "73939133" << endl;
              return 0;
          } 
          Euler();
          for(int i = 1;i <= cnt;i ++) {//拆分质数
              int x = prime[i] / 10;
              for(int j = 1;j <= n;j ++) {
                  if(vis[x] != 0 || x == 1) f = 1;
                  x /= 10; 
              }
              if(f == 0 && prime[i] >= m / 10) printf("%d\n",prime[i]);
              f = 0;
          }
          return 0;
      }
------------
搜索（回溯）：13ms

      #include <cstdio>
      int a[10] = {0,1,3,7,9},ans[10],n;//剪枝：质数的末尾只能是1,3,7,9
      bool Prime(int x) {//最简单的方法判断质数
          if(x == 2) return true;
          if(x % 2 == 0) return false;
          for(int i = 3;i *  i <= x;i += 2) if(x % i == 0) return false;
          return true;
      }
      void print(int n) {
          for(int i = 1; i <= n; i ++) printf("%d",ans[i]);
          printf("\n");
      }//以ans记录数位上的数，满足条件则输出
      void dfs(int i,int sum) {//i是当前第几个，sum是总和
          if(Prime(sum) == false) return;//不是质数就返回
          if(i == n + 1) print(n);//凑齐就输出
          for(int j = 1; j <= 4; j ++) ans[i] = a[j],dfs(i + 1,sum * 10 + a[j]),ans[i] = 0；//加上数位，搜下一层，回溯
      }
      int main() {
          scanf("%d",&n);
          ans[1] = 2,dfs(2,2);//第一位只能是2,3,5,7
          ans[1] = 3,dfs(2,3);
          ans[1] = 5,dfs(2,5);
          ans[1] = 7,dfs(2,7);
          return 0;
      }

------------
打表： 12ms（1-8当然打表啊）

优点：~~代码简洁方便食用~~

   
     #include <cstdio>
      int main() {
          int n;
          scanf("%d",&n);
          if(n == 1) printf("2\n3\n5\n7");
          if(n == 2) printf("23\n29\n31\n37\n53\n59\n71\n73\n79");	
          if(n == 3) printf("233\n239\n293\n311\n313\n317\n373\n379\n593\n599\n719\n733\n739\n797");
          if(n == 4) printf("2333\n2339\n2393\n2399\n2939\n3119\n3137\n3733\n3739\n3793\n3797\n5939\n7193\n7331\n7333\n7393");
          if(n == 5) printf("23333\n23339\n23399\n23993\n29399\n31193\n31379\n37337\n37339\n37397\n59393\n59399\n71933\n73331\n73939");
          if(n == 6) printf("233993\n239933\n293999\n373379\n373393\n593933\n593993\n719333\n739391\n739393\n739397\n739399");
          if(n == 7) printf("2339933\n2399333\n2939999\n3733799\n5939333\n7393913\n7393931\n7393933");
          if(n == 8) printf("23399339\n29399999\n37337999\n59393339\n73939133");
          return 0;
    }




---

## 作者：GEM_IU_077 (赞：2)

###dfs(pascal)！！！

本题采用方法：深度优先搜索+条件剪枝。问题的本质就是寻找一个n位的质数，然后逐位去掉末尾，要求该形成的新数也是质数。根据样例数据分析可以采用末尾补奇数的方式，然后判断该数是否为质数。即逐步深搜添加的数值为**1、3、5、7、9**，同时对该数进行判断是不是质数（素数），是则递归处理下一位数，不是则剪枝回溯，直到**depth>n**。 或者直接深搜**1～9**，然后条件判断是不是质数（素数），是则递归处理下一位数，不是则剪枝回溯，直到**depth>n**。

下附代码：

```pas
var
  n,s,ans:longint;
  a:array[0..5] of longint=(2,1,3,5,7,9);

function zs(x:longint):boolean;
  var
    i:longint;
  begin
    if x=1 then exit(false);
    for i:=2 to trunc(sqrt(x)) do
      if x mod i=0 then exit(false);
    exit(true);
  end;

procedure dfs(s:longint);
  var
    i:longint;
  begin
    if s>n
      then
        begin
          writeln(ans);
          exit;
        end;
    for i:=0 to 5 do
      begin
        if zs(ans*10+a[i])
          then
            begin
              ans:=ans*10+a[i];
              dfs(s+1);
              ans:=ans div 10;
            end;
      end;
  end;

begin
  readln(n);
  s:=1;
  dfs(1);
end.
```

---

## 作者：加载错误 (赞：2)

# 我发现大家全部用的是DFS，本小牛来一个线性筛素数法。
### 重要的线性筛素数法子函数：
```cpp
void ss(int n)//线性筛素数法 
{
	zs[0] = 1;
	zs[1] = 1;
	zs[2] = 0;
	zs[3] = 0;
	zs[4] = 1;
    for(register int i = 1;i * i <= n;i++)//用register int 在循环里面大幅节约时间 
    {
        if(zs[i] == 1)
            continue;
        for(register int j = 2;i * j <= n;j++)
            zs[i * j] = 1;
    }
}
```
###### 因为线性筛素数法的局限性，所以不得不无奈地打表| _ |
```cpp
if(n==8)
{
    cout<<"23399339"<<endl<<"29399999"<<endl<<"37337999"<<endl<<"59393339"<<endl<<"73939133"<<endl;
    return 0;
}
```
## O**K,上代码：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
bool zs[100000010];//用bool型，节约资源。。。 
void ss(int n)//线性筛素数法 
{
	zs[0] = 1;
	zs[1] = 1;
	zs[2] = 0;
	zs[3] = 0;
	zs[4] = 1;
    for(register int i = 1;i * i <= n;i++)//用register int 在循环里面大幅节约时间 
    {
        if(zs[i] == 1)
            continue;
        for(register int j = 2;i * j <= n;j++)
            zs[i * j] = 1;
    }
}
bool ok(int x,int n)//拆分函数 
{
	if(n == 1)
		return zs[x];
	for(int i = 0;i < n;i++)
	{
		int y = x,t = i;
		while(t--)//拆分（主体） 
			y /= 10;//每次除以10的次数递增，做到题中的要求 
		if(zs[y])//判断素数，如果不是直接回去 
			return false;
	}
	return true;
}
int main()
{
	int n,m;
	cin>>n;
	if(n==8)//打表大法好，神犇勿喷 
    {
        cout<<"23399339"<<endl<<"29399999"<<endl<<"37337999"<<endl<<"59393339"<<endl<<"73939133"<<endl;
        return 0;//直接退出 
    }
	int x = pow(10,n - 1) + 1,//最小的n位数，因为末尾有零的数不是素数，直接加1 
		y = pow(10,n) - 1;//最大的n位数 
	ss(y);// 线性筛素数法 
	for(int i = x;i <= y;i+=2)//遍历整个n位数集合 
	{
		if(ok(i,n))//传递数和这个数的位数 
			cout<<i<<endl;
	}
	return 0;//程序拜拜 
}
```

---

## 作者：「QQ红包」 (赞：1)

题解by：redbag

原文地址：http://redbag.duapp.com/?p=1091

这道题有几种解法，我用的是dfs。

当然做了几个小剪枝，

由题可知，第一位可为2,3,5,7。

后面的每一位只能为1,3,7,9。

所以只需要搜这几个数。

然后判断加入下一位后是否为质数，如果不是质数的话就无需往后搜了。

代码如下

/\*
ID: ylx14271

PROG: sprime

LANG: C++

\*/
>#include<set>
>#include<map>
>#include<list>
>#include<queue>
>#include<stack>
>#include<string>
>#include<time.h>
>#include<math.h>
>#include<memory>
>#include<vector>
>#include<bitset>
>#include<fstream>
>#include<stdio.h>
>#include<utility>
>#include<sstream>
>#include<string.h>
>#include<iostream>
>#include<stdlib.h>
>#include<algorithm>
>#define LL unsigned long long
>int n;
>int a[9];
>using namespace std;
>int pd(int xx)//判断质数
>{
>if (xx==1) return 0;//1不是质数
>for (int i=2;i<=sqrt(xx);i++)
>if (xx%i==0)//能整除
>return 0;//0代表不是质数
>return 1;//否则就是质数
>}
>void dfs(int nn,int t)
>{
>if (t==n)//如果搜完了
>{
>cout<<nn<<endl;//不需要再判断是否为质数
>//因为在搜索过程中已经判断过了
>return;//退出
>}
>int nnn=nn\*10+1;
>if (pd(nnn)==1)//如果这个数是质数的话就继续往下搜
>dfs(nnn,t+1);
>nnn=nn\*10+3;
>if (pd(nnn)==1)//如果这个数是质数的话就继续往下搜
>dfs(nnn,t+1);
>nnn=nn\*10+7;
>if (pd(nnn)==1)//如果这个数是质数的话就继续往下搜
>dfs(nnn,t+1);
>nnn=nn\*10+9;
>if (pd(nnn)==1)//如果这个数是质数的话就继续往下搜
>dfs(nnn,t+1);
>}
>int main()
>{
>freopen("sprime.in","r",stdin);
>freopen("sprime.out","w",stdout);
>scanf("%d",&n);
>if (n==1) printf("2\n3\n5\n7\n");//1的话直接打表就好了
>dfs(2,1);dfs(3,1);dfs(5,1);dfs(7,1);//深搜
>return 0;
>}

---

## 作者：远航之曲 (赞：1)

直接枚举法

预处理求出长度1~8所有符合条件的质数,方法很简单,而且效率极高. N=1的时候,只有2,3,5,7，N>1的时候,每一位只能是1,3,7,9.所以先求出N=1的素数,再用N=1的素数加上1,3,7,9，符合条件的数形成N=2的素数.再用N=2的用同样办法求出N=3的,以此类推. 动态规划法

设primes[i][\*]保存位长为i的所有质数，size[i]表示位长为i的质数的个数。那么我们可以根据primes[i][\*]的内容很快求出primes[i+1][\*]的内容。

对所有的primes[i][j],因为个位上只可能是tail[4]={1,3,7，9}，对k=0 to 3,所以检查primes[i][j]\*10+tail[k]是否是质数，若是，保存在primes[i][size[i]++]中；伪代码如下：

[/color][codep ]

```cpp
for i 1 to n-1
  for j 0 to size[i-1]-1
      for k 0 to 3
          if(isPrime(primes[i-1][j]*10+tail[k])) 
              primes[i][size[i]++]=primes[i-1][j]*10+tail[k];
```
[/codep ]
当然，可以打表，程序如下。

[/color][codec ]

```cpp
#include <iostream>
using namespace std;
const char lut[9][200]=
{
```
"",
"2\n3\n5\n7\n",

"23\n29\n31\n37\n53\n59\n71\n73\n79\n",

"233\n239\n293\n311\n313\n317\n373\n379\n593\n599\n719\n733\n739\n797\n",

"2333\n2339\n2393\n2399\n2939\n3119\n3137\n3733\n3739\n3793\n3797\n5939\n7193\n7331\n7333\n7393\n",

"23333\n23339\n23399\n23993\n29399\n31193\n31379\n37337\n37339\n37397\n59393\n59399\n71933\n73331\n73939\n",

"233993\n239933\n293999\n373379\n373393\n593933\n593993\n719333\n739391\n739393\n739397\n739399\n",

"2339933\n2399333\n2939999\n3733799\n5939333\n7393913\n7393931\n7393933\n",

"23399339\n29399999\n37337999\n59393339\n73939133\n"

};
int n;
int main(){cin>>n;cout<<lut[n];return 0;};

[/codec ]


---

## 作者：Reanap (赞：1)

#     模拟大法好哇！
    
    （咱要正经一点）
    这道题我们可以模拟特殊质数产生的过程，从而得出结果
    
     显然，在这之中必然涉及到质数判定，我们可以用
####      Miller_Robin算法
	  （其实用不用速度差不多）
    #include <cstdio>
    #include <ctime>
    #include <cmath>
    #include <algorithm>
    typedef long long LL;
    using namespace std;
    int n;

    LL modular_exp(LL a,LL m,LL n) {
        if(m == 0) return 1;
        if(m == 1) return (a % n);
        LL w = modular_exp(a,m/2,n);
        w = w * w % n;
        if(m & 1) w = a * w % n;
        return w;
    }

    bool Miller_Robin(LL n) {
        if(n==1) return false;
        if(n==2) return true;
        for(int i=1; i<=10; ++i) {
            LL a = rand() % (n - 2) + 2;
            if(modular_exp(a,n,n) != a) return false;
        }
        return true;
    }
    //Miller_Robin不解释

    void find(int t,int ans) {
        for(int i=1;i<=9;++i) {		//一位一位地找
            if(Miller_Robin(ans*10+i)) {
                if(t==n) printf("%d\n",ans*10+i);
                	//数位满足则输出
                else find(t+1,ans*10+i);
                	//否则继续找
            }
        }
    }

    int main() {
        srand(time(NULL));
        scanf("%d",&n);
        find(1,0);
        return 0;
    }

---

## 作者：Electrified (赞：1)

本弱的第一篇题解，欢迎指教。

原来这题不会做，想看题解的时候突然发现dalao们用的都是本弱还没学的搜索，瞬间心态爆炸；然后就想到了埃氏筛的做法，又看楼下有篇打表的埃氏题解，就想贴一篇自己的题解。欢迎各位dalao批评指正。

```
#include<bits/stdc++.h>
using namespace std;
```

惯例的万能头文件和使用标准库。

```
bool if_prime(int x)
{
	if(x==1)return 0;
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0)return 0;
    }
    return 1;
}

```

这是判断素数的方法，相信不用多说。特判1最好还是加上，虽然主程序里没用。

```
int n,q[1000],k,ans;
bool p[8000000];
int main()
{
    scanf("%d",&n);
```

本题需要的变量以及变量输入。因为8位数用埃氏筛会TLE，又因为合要求的数开头只会是2、3、5、7，所以开八百万就可以了。

```
if(n==1)
    {
    	printf("2\n3\n5\n7");
        return 0;
    }
```
特判1。其实并没有什么用，因为数据点里没有1。

```
p[1]=1;
n=(int)(pow(10,n));
```

把1定义为非素数（因为本弱不会用memset，又已知数组定义在主函数外面默认定义为0，所以在这个程序里1为不合要求的数，0为合要求的数）。把n变成所有数的上限。

```
for(int i=2;i<=min(7999999,n);i++)
{
    if(p[i]==0)
    {
        for(int j=2;i*j<=min(7999999,n);j++)
        {
            p[i*j]=1;
        }
        if(p[i/10]==1)p[i]=1;
    }
}
```

程序的核心。这里是为了减少时间用了min函数，其实不用也可以过。这里先找没有被定义成不合要求的数的数（即素数），把这上面所有它的倍数定义成合数。之后再看它合不合要求（就是看这个数除以10之后合不合要求）。

```
if(n<1e8)
    for(int i=2*n/10+1;i<8*n/10;i+=2)
    {
        if(p[i]==0)printf("%d\n",i);
    }
```

看2到7位数的情况。因为合要求的数必须是奇数并且以2、3、5、7开头，所以只用枚举2字头到8字头。

```
else
{
    for(int i=2*n/100+1;i<8*n/100;i+=2)
    {
        if(p[i]==0)q[++k]=i;
    }
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<10;j+=2)
        {
        	if(j==5)continue; 
            ans=q[i]*10+j;
            if(if_prime(ans))printf("%d\n",ans);
        }
    }
}
```

对8位数进行特判（因为直接筛会T），先找出合要求的7位数，再在后面添1、3、7或9，判断它是不是素数，是就直接输出。

```
    return 0;
}
```
程序的结束。

## 谢谢观看！！


---

## 作者：Eureka_sr (赞：0)

##**嘿嘿，看到下面并没有我这么鬼畜的想法，于是来一发题解**

###**欧拉筛，害怕吗= =，但是弊端是【由于我菜** ##**最后的8只能打表过**

###emmmm。。。是这样的，上面裸的欧拉筛应该都会，在此不讲解

###主要是下面主体部分，请看代码注释。



```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=10000010;
int p[maxn],a[maxn];
bool b[maxn],f;
int n,m,cnt;
void work()//裸欧拉筛
{
    for(int i=2;i<=m;i++)
    {
        if(!b[i])
            p[++cnt]=i;
        for(int j=1;j<=cnt&&i*p[j]<=m;j++)
        {
            b[i*p[j]]=1;
            if(i*p[j]==0)
                break;
        }
    }    
}
int main()
{
    cin>>n;
    m=pow(10,n);//m就是欧拉筛的范围
    if(n==8)//无奈打表的点
    {
        cout<<"23399339"<<endl<<"29399999"<<endl<<"37337999"<<endl<<"59393339"<<endl<<"73939133"<<endl;
        return 0;
    }
    work();
    for(int i=1;i<=cnt;i++)//对于我们已经筛出来的质数枚举
    {
        int x=p[i]/10;//按题意取出“肋骨”
        for(int j=1;j<=n;j++)
        {
            if(b[x]!=0||x==1)//一定要判1 ！！！！！
                f=1;//标记一下
            x/=10;
        }
        if(f==0&&p[i]>=(m/10))//有题目知我们需要的是m/10~m范围内的质数
            printf("%d\n",p[i]);
        f=0;//还原一下标记别忘了
    }
    return 0;
}
```

---

## 作者：feecle6418 (赞：0)

俗话说：打表大法好！

由于这一题暴力会TLE,所以我在暴力中间穿插了打表，使它不会超时。具体可以看代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
inline bool isin(int x,int n) {//打表函数1：判断x是否在n的数位上出现，节省时间，避免做不必要的质数判断
    while(n) {
        if(n==0&&x==0)return false;
        if(x%10==n)return true;
        n/=10;
    }
    return false;
}
inline bool prime(int n) {//判断质数函数
    int i;
    if(n==3||n==2)return 1;
    if(n<=1)return 0;
    for(i=2; i<=sqrt(n); i++) {
        if(n%i==0) {
            return false;
        }
    }
    return true;
}
int main() {
    int i,j,m=8,g=0,bj,u;
    cin>>m;
    //当当当当！开始打表！
    for(i=2*pow(10,m-1); i<8*pow(10,m-1); i++) {//打表1：只需要从2枚举到8
        //下面打表2：避免做不必要的循环
        //当m=7时的打表
        if(m==7&&i==2000000)i=2330000;
        if(m==7&&i==2340000)i=2390000;
        if(m==7&&i==2400000)i=2930000;
        if(m==7&&i==2940000)i=3730000;
        if(m==7&&i==3740000)i=5930000;
        if(m==7&&i==5940000)i=7390000;
        if(m==7&&i==7400000)break;
        //-------------------------------打表分界线1-------------------------------//
        //当m=8时的打表
        if(m==8&&i==20000000)i=23390000;
        if(m==8&&i==23400000)i=29390000;
        if(m==8&&i==29400000)i=37330000;
        if(m==8&&i==37340000)i=59390000;
        if(m==8&&i==59400000)i=73930000;
        if(m==8&&i==73940000)break;
        //-------------------------------打表分界线2-------------------------------//
        if(isin(4,i)||isin(6,i)||isin(8,i)||isin(0,i))continue;//打表3：判断在i的数位里是否出现非质偶数
        if(i%3==0||i%7==0||i%11==0||i%13==0)continue;//打表4：先简单的过滤一下
        //-------------------------------打表分界线3-------------------------------//
        u=i;
        while(u) {
            if(!prime(u))break;
            u=u/10;
        }
        if(u==0) cout<<i<<endl;
    }
    return 0;
}
```

---

## 作者：ylsoi (赞：0)

我前面写打表没有通过（可能在讨论区还有我的打表大法），于是现在来一发正常一点啊；

因为除了2之外，只有奇数才会是质数，所以第一位只要枚举2,3,5,7,而后面的数位只要枚举1，3，5，7，9就可以了啊；

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
using namespace std;
int n,a[6]={0,1,3,5,7,9};//呵呵，这是用来枚举的啊
bool prime(int n)//质数判断
{
    if(n==1)return 0;
    if(n==2)return 1;
    for(int i=2;i*i<=n;i++)
    if(n%i==0)return 0;
    return 1;
}
void dfs(int k,int sum)
{
    if(prime(sum)==0)return;//这算是一种剪枝吧，如果当前数都不是素数的话，那我还搜下去干什么(⊙v⊙)；
    if(k==n)
    {
        printf("%d\n",sum);//如果集齐了N个数位，就可以召唤神龙（输出和换行）！！！
        return;
    }
    for(int i=1;i<=5;i++)
    dfs(k+1,sum*10+a[i]);//拓展节点
}
int main()
{
    scanf("%d",&n);
    dfs(1,2);//这还有什么好说的吗？？
    dfs(1,3);
    dfs(1,5);
    dfs(1,7);
    return 0;
}

```

---

## 作者：ljc20020730 (赞：0)

下面的打表真的是无厘头，建议删除

~~忍不住吐槽~~

下面的pascal解法有些太繁琐，这里来一发简单明了的

当然大家可以创立质数表（高深的东西）

这里用的是一个叫做Miller Rabbin的判断质数法

就是利用费马小定理：当 p 为 质数的时候 ,a^(p-1) mod p = 1

其中 a,p 要互质

如果 a^ (p-1) mod p = 1 那么 p 很有可能是质数 (大约75%的概率)

如果 a^ (p-1) mod p 1 那么 p 一定 不是质数

如果你对每个p 拿 count=30 个数去检验

那么出错的概率为 (0.25)^count 是很小很小的数字

所以 Miller-Rabbin 算法是很有效的求质数的方法

（别的算法要么 O(n) 要么 O(sqrt(n)),这个算法是 O（count\*log(n)） 的其中count 是一个常数）

当n比较大的话，可以用Miller Rabbin可以判断质数10000个longint范围内数据而不超时

于是……

一位一位搜就可以（并不用剪枝）模板2

```cpp
procedure dfs(k:longint; num:longint);
var i:longint;
begin
 for i:=1 to 9 do//末尾加什么数字（0的话不考虑，加了是合数）
  if pd(num*10+i) then begin//如果新产生的数是质数
   if k=n then writeln(num*10+i)//如果位数达到要求就输出
   else dfs(k+1,num*10+i);//否则再深搜
  end;
end;
```
献上标程：
var n:longint;

function pow(x,n,k:qword):qword overload;

{Miller Rabbin判断素

如果n是一个正整数，如果存在和n互素的正整数a满足a^(n-1)≡1(mod n)，我们说n是基于a的伪素数。O(slogn) n为合数的几率为1/2^s}

```cpp
begin
 if n=0 then exit(1);
 pow:=pow(x,n div 2,k) mod k;
 pow:=pow*pow mod k;
 if n mod 2=1 then pow:=pow*x mod k;
end;
function pd(n:longint):boolean overload;
var m:qword;
      i:longint;
begin
  randomize;
  if n=1 then exit(false);
  for i:=1 to 30 do begin
    m:=random(n-2)+1;
    if pow(m,n-1,n)<>1 then exit(False);
  end;
  exit(True);
end;
```
{普通法判断素数
```cpp
function pd(x:longint):boolean;
var i:longint;
begin
 if x=1 then exit(false);
 for i:=2 to trunc(sqrt(x))do
  if x mod i=0 then exit(false);
 exit(true);
end;}
procedure dfs(k:longint; num:longint);
var i:longint;
begin
 for i:=1 to 9 do
  if pd(num*10+i) then begin
   if k=n then writeln(num*10+i)
   else dfs(k+1,num*10+i);
  end;
end;
begin
 readln(n);
 dfs(1,0);
end.

```

---

## 作者：ZYR_ (赞：0)

从实验和分析中可以发现，**每个质数肋骨的首位一定是2、3、5、7之一；往后的每一位一定是1、3、7、9之一。（不信你试试）**知道这个就好办了。再进行简单的搜索枚举和模拟，结果就出来了。代码如下：

```cpp
var
    n:integer;
    i:longint;
function ss(n:string):boolean;  //判断素数，不用多说了吧！
var    
    t,tt,i:longint;  //切记数字范围要开大！
begin
    val(n,t,tt);
    if t=1 then exit(false);
    for i:=2 to trunc(sqrt(t)) do
        if t mod i=0 then exit(false);
    exit(true);
end;
procedure find(s:string);
begin
    if length(s)=n then begin writeln(s); exit; end;
    if ss(s+'1') then find(s+'1');  //尝试后一位是1的情况
    if ss(s+'3') then find(s+'3');  //尝试后一位是3的情况
    if ss(s+'7') then find(s+'7');  //尝试后一位是7的情况
    if ss(s+'9') then find(s+'9');  //尝试后一位是9的情况
end;
begin
    readln(n);
    find('2');  //尝试四个首位数字
    find('3'); 
    find('5'); 
    find('7');  
end.
理清思路，找到方法，此题不难。
```

---

## 作者：Ufowoqqqo (赞：0)

楼下用的是bfs而本人不才只会用dfs，幸好侥幸ac。

思路：肯定由2、3、5和7打头，因为最后要切到只剩一根肋骨，彼时要判断最高位是否质数，所以要由一位的质数作开头；后面则不限定了，但个位为偶数的一定能被2整除，所以只能是奇数；同时以5结尾也一定能够被5整除所以5也不行，排除完之后不断加[delete]（特技）[/delete]最低位，直到够n位。

同时要剪枝，裸的dfs太耗时，若当前的数已非质数那么再搜也就没有意义了，直接返回上一层。

```delphi

var n:longint;
function prime(n:longint):boolean;
var i:longint;
begin
 prime:=true;
 for i:=2 to trunc(sqrt(n)) do if n mod i=0 then exit(false);
end;
procedure search(s:string);
var t:longint;
begin
 val(s,t);
 if not prime(t) then exit;//剪枝
 if length(s)=n then
  begin
   writeln(s);//长度匹配且经历了剪枝的考验，可以输出了！
   exit;
  end;
 search(s+'1');
 search(s+'3');
 search(s+'7');
 search(s+'9');
end;
begin
 read(n);
 search('2');
 search('3');
 search('5');
 search('7');
end.

```

---

## 作者：一碗粥 (赞：0)

发题解了！

这道题目还是蛮简单的，广搜+生成法，这里就不多介绍了。首先，我们要注意的是个位数是质数的情况，只有2，3，5，7（如const数组a）能符合要求。再来，如果n<>1，那么在2，3，5，7后面生成的数字只能是1，3，7，9（2，4，6，8，0是偶数，5结尾一定能被5整除），随后用字符串在队列中生成即可。

标程：

```delphi
const a:array[1..4]of longint=(2,3,5,7);
      b:array[1..4]of longint=(1,3,7,9);//上面说过。
var i,j,k,l,m,n,sum,t,w:longint;
    s,s1,s2,s3,ss:string;
    dl:array[1..1000000]of string;
function pd(x:longint):boolean;//判断是否是质数
var j:longint;
begin
  for j:=2 to trunc(sqrt(x)) do
  if x mod j=0 then exit(false);
  exit(true);
end;
begin
  read(n);
  for i:=1 to 4 do str(a[i],dl[i]);
  t:=1;
  w:=5;
  while t<w do//广搜
  begin
    for i:=1 to 4 do
    begin
      str(b[i],s1);
      s1:=dl[t]+s1;//生成
      val(s1,m);
      if pd(m) then dl[w]:=s1;//放进队列
      if length(dl[w])=n then writeln(dl[w]);
      if length(dl[t])=n then halt;//嗯，如果头指针指向的字符串长度为n，那么说明接下来要生成的字符串为n+1位，直接退出！
      inc(w);
    end;
    inc(t);
  end;
end.
```
谢谢阅读！


---

## 作者：Komorebi_shine (赞：0)

### 给大家介绍一个清奇的解法
我们通过阅读下面的打表题解可以发现，即使在8位数的范围内，题目中要求的特殊质数也屈指可数。

我们还发现，一个数只有当它的1/10是特殊质数时，它才*有可能*是特殊质数。

因此可以设计出一个递推的做法：

先打表把1位数的质数打好，接下来从2~n位依次处理，每次在前一位的特殊质数的基础上乘上10再加上一个数，再判断这个数是否是质数，如果是质数，它就是特殊质数，存进表中，等待使用。最后输出n位的所有数就好了。

有点类似于递推/记搜

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[9][31],i,j,k
;
bool prime(int x)
{
	int ii;
	for (ii=2;ii<=(int)ceil(sqrt(x));ii++)
	 if (!(x%ii)) return false;
	return true;
}
int main()
{
    scanf("%d",&n);
    a[1][1]=2;
    a[1][2]=3;
    a[1][3]=5;
    a[1][4]=7;
    a[1][0]=4;
    for (i=2;i<=n;i++)
     for (j=1;j<=a[i-1][0];j++)
      for (k=1;k<=9;k+=2)
      {
      	if (prime(a[i-1][j]*10+k))
      	{
      		a[i][++a[i][0]]=a[i-1][j]*10+k;
      	}
      }
    for (i=1;i<=a[n][0];i++) printf("%d\n",a[n][i]);
}
```

~~**这题难度怎么评出来的，反正我评了普及/提高-**~~

---

## 作者：youzhifei (赞：0)

这道题数据很大（~~我才不说我3个测试点TLE了~~）
  废话少说，这道题主要考
#   素数筛以及递归
（我这么做的）


------------
```
int zhis(int n){//函数，0为非质数，1为质数
	if(n==1)//特判一
	return 0;
	for(int i=2;i<=sqrt(n);i++){//从2到n的平方根
		if(n%i==0)//如果除得尽，返回0
		{
			return 0;
		}
	}
	return 1;//质数
}
```


------------
质数判断好了以后，题目是n个位数的数，so做2个函数判断区间


------------
```
int x(int n){//最小数1加上n-1个0
	int s=1;
	for(int i=1;i<n;i++){
		s*=10;
	}
	return s;
}
int x2(int n){//最大数1加上n个0再减1
	int s=1,h;
	for(int i=0;i<n;i++){
		s*=10;
	}
	h=s/10;
	return s-1-h*2;
}
```


------------
素数判断好了，开始判断数字了；


------------
```
int lang(int n){//递归函数
	if(n/10==0&&zhis(n%10)!=0){//根基判断
		return 1;
	}
	if(zhis(n)==1){//参见第一个函数
		return lang(n/10)*1;
	}
	else if(zhis(n)==0){//参见第一个函数
		return lang(n/10)*0; 
	}
}
```


------------
好的，贴上完整代码


------------
```
#include<bits/stdc++.h>
using namespace std;
int zhis(int n){
	if(n==1)
	return 0;
	for(int i=2;i<=sqrt(n);i++){
		if(n%i==0)
		{
			return 0;
		}
	}
	return 1;
}
int x(int n){
	int s=1;
	for(int i=1;i<n;i++){
		s*=10;
	}
	return s;
}
int x2(int n){
	int s=1,h;
	for(int i=0;i<n;i++){
		s*=10;
	}
	h=s/10;
	return s-1-h*2;
}
int lang(int n){
	if(n/10==0&&zhis(n%10)!=0){
		return 1;
	}
	if(zhis(n)==1){
		return lang(n/10)*1;
	}
	else if(zhis(n)==0){
		return lang(n/10)*0; 
	}
}
int main(){

	int n,h;
	cin>>n;
		for(int i=x(n)*2;i<=x2(n);i++){
			if(lang(i)==1){
				cout<<i<<endl;
			}
	    }
	
		return 0;
} 
```


------------
上是完整的  _**TLE**_ 代码 
于是，就有了以下利用以上代码的打表AC代码
------------

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	if(n==1){
		cout<<"2"<<endl<<"3"<<endl<<"5"<<endl<<"7"<<endl;
	} 
	if(n==2){
	cout<<"23"<<endl<<"29"<<endl<<"31"<<endl<<"37"<<endl<<"53"<<endl<<"59"<<endl<<"71"<<endl<<"73"<<endl<<"79"<<endl;
	}
	if(n==3){
	cout<<"233"<<endl<<"239"<<endl<<"293"<<endl<<"311"<<endl<<"313"<<endl<<"317"<<endl<<"373"<<endl<<"379"<<endl<<"593"<<endl<<"599"<<endl<<"719"<<endl<<"733"<<endl<<"739"<<endl<<"797"<<endl;
	}
	if(n==4){
	cout<<"2333"<<endl<<"2339"<<endl<<"2393"<<endl<<"2399"<<endl<<"2939"<<endl<<"3119"<<endl<<"3137"<<endl<<"3733"<<endl<<"3739"<<endl<<"3793"<<endl<<"3797"<<endl<<"5939"<<endl<<"7193"<<endl<<"7331"<<endl<<"7333"<<endl<<"7393"<<endl;
	}
	if(n==5){
	cout<<"23333"<<endl<<"23339"<<endl<<"23399"<<endl<<"23993"<<endl<<"29399"<<endl<<"31193"<<endl<<"31379"<<endl<<"37337"<<endl<<"37339"<<endl<<"37397"<<endl<<"59393"<<endl<<"59399"<<endl<<"71933"<<endl<<"73331"<<endl<<"73939"<<endl;
	}
	if(n==6){
	cout<<"233993"<<endl<<"239933"<<endl<<"293999"<<endl<<"373379"<<endl<<"373393"<<endl<<"593933"<<endl<<"593993"<<endl<<"719333"<<endl<<"739391"<<endl<<"739393"<<endl<<"739397"<<endl<<"739399"<<endl;
	}	
	if(n==7){
	cout<<"2339933"<<endl<<"2399333"<<endl<<"2939999"<<endl<<"3733799"<<endl<<"5939333"<<endl<<"7393913"<<endl<<"7393931"<<endl<<"7393933"<<endl;
	}
	if(n==8){
	cout<<"23399339"<<endl<<"29399999"<<endl<<"37337999"<<endl<<"59393339"<<endl<<"73939133"<<endl;
	}
}
```

------------
感谢今日制造（1……



---

## 作者：水库中的水库 (赞：0)

这道题很明显一个线性筛

每次都从第一位数开始枚举，每一次都添加一位，保证这个都是素数即可

但$n=8$会超空间，只能打一个表...

```cpp
/***************************************************************
	File name: P1218.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 08时49分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100000010;

int prime[maxn], v[maxn], m, n, p = 1;

inline void DFS(int sum, int x)
{
	if ( sum == 0 && x != 1 ) return ;
//	printf("%d %d\n", sum, x);
	if ( x == n + 1 )
	{
		printf("%d\n", sum);
		return ;
	}
	sum *= 10; int k;
	REP(i, 0, 9) 
	{
		k = sum + i;
		if ( v[k] == k ) DFS(k, x + 1);	
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	if ( n == 8 )
    {
        cout << "23399339" << endl << "29399999" << endl << "37337999" << endl << "59393339" << endl << "73939133" << endl;
        return 0;
    }
	REP(i, 1, n) p *= 10;
	REP(i, 2, p)
	{
		if ( v[i] == 0 ) { v[i] = i; prime[++ m] = i; }
		REP(j, 1, m)
		{
			if ( prime[j] > i || prime[j] * i > p ) break ;
			v[i * prime[j]] = prime[j];
		}
	}
	DFS(0, 1);
    return 0;
}
```

---

## 作者：EnderXie (赞：0)

不dfs，不打表的做法...

先上代码（c++11，由于用了to_string和atoi）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ind;
bool is_p(int n){//O(sqrt(n)/3)的算法，具体参考
	//https://blog.csdn.net/songyunli1111/article/details/78690447
	if(n==1) return false;
	if(n==2 || n==3) return true;
	if(n%6!=1 && n%6!=5) return false;
	float _n=floor(sqrt((float)n));
	for(int i=5;i<=_n;i+=6)
		if(n%i==0 || n%(i+2)==0)
			return false;
	return true;
}
int is(int x){//用来判断是否符合标准
	string temp=to_string(x);
	for(unsigned int i=1;i<=temp.size();i++)
		if(!is_p(atoi(temp.substr(0,i).c_str()))) return i;
    //（高能）这里返回的i是不符合标准的位数
	return 0;
}
int main(){
	cin>>ind;
	for(register int i=pow(10,ind-1)+1;i<pow(10,ind);i++){
    	//register int加快速度
		int ans=is(i);
		if(ans==0)
			cout<<i<<"\n";
		else i+=pow(10,ind-ans)-1;//直接在不符合标准的位数上加1
	}
	return 0;
}
```

这种算法大幅度的加快了枚举的速度，使枚举成为可能

---

## 作者：Sino_E (赞：0)

题目要我们求长度为n的特殊质数。

首先长度为n的特殊质数肯定建立在长度为n-1的特殊质数上才符合条件。

于是我们先求出长度为1的质数，再在这个质数上枚举加上0~9的数字，判断是不是质数，以此来得到长度为2的特殊质数。

以此类推，可以得到长度为3的、长度为4的、一直到n。

循环枚举模拟，暴力判断是否为质数即可。

复杂度讲道理是不高的。因为从长度为1开始这种质数就很少嘛。

其它的质数判断就不多讲啦~

下面是代码。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5;
int pri[N],p;   //现有的质数
int npri[N],np; //新处理的质数    
inline bool ispri(int x){
    if(x==0||x==1) return false;
    for(int i=2;i*i<=x;i++)
        if(x%i==0) return false;
    return true;
}   //暴力判断是否为质数

int main(){
    int n;
    cin>>n;
    p=1;    //初始化时长度为0，即由数字0推得长度为1的特殊质数
    for(int i=1;i<=n;i++){
        np=0;
        for(int j=0;j<p;j++)
            for(int k=0;k<=9;k++)   //枚举质数和新加上的数字
                if(ispri(pri[j]*10+k))npri[np++]=pri[j]*10+k;   //若i-1长度的质数加上了该数字仍是质数，则放入新的i长度的质数数组当中。
        memcpy(pri,npri,sizeof(npri));  //复制数组
        p=np;
    }
    for(int i=0;i<p;i++) printf("%d\n",pri[i]);
    return 0;
}
```

---

## 作者：Wax_Gourd (赞：0)

这道题一开始超时了，以下是超时代码：

```cpp
#include<cstdio>
#include<cmath>
int n,l,_r,r,t;
bool vis[100000001],flag;
void init(){
    _r=sqrt(r)+0.5;
    for(int i=2;i<=_r;i++)
        if(!vis[i]){
            for(int j=i*i;j<=r;j+=i)
                vis[j]=true;
        }
    vis[1]=true,vis[2]=false;
}
int main(){
    scanf("%d",&n);
    l=pow(10,n-1),r=pow(10,n)-1;
    init();
    for(int i=l;i<=r;i++){
        t=i,flag=false;
        while(t>0){
            if(vis[t]) flag=true;
            t/=10;
        }
        if(!flag) printf("%d\n",i);
    }
}
```
实在是水平有限，我~无可奈何~，只好根据源代码先算出来，打表过（你认为我会给你代码吗？）。
后来我一拍脑门——有规律！

一位的就不用马赛克了——2、3、5、7，那么2位的“特殊的质数肋骨”其实是在这四个数的后面加上几个数（偶数（包括2）不考虑，5不考虑，只看1，3，7，9）；当然如果你认为后面的数这样算起来还麻烦，就应该想到——n位的“特殊的质数肋骨”应该建立在n-1位的“特殊的质数肋骨”之上（还要我证明吗！），此题得解。


---

## 作者：mr辄 (赞：0)

**这题最好用深度优先搜索+条件剪枝。问题的本质就是寻找一个n位的质数，然后逐位去掉末尾，要求该形成的新数也是质数。根据样例数据分析可以采用末尾补奇数的方式，然后判断该数是否为质数。即逐步深搜添加的数值为1、3、5、7、9，同时对该数进行判断是不是质数（素数），是则递归处理下一位数，不是则剪枝回溯，直到depth>n。 或者直接深搜1～9，然后条件判断是不是质数（素数），是则递归处理下一位数，不是则剪枝回溯，直到depth>n。

当然在处理完该4位数是质数后需要记录该数。**


#然后我们就可以的出程序：




```cpp
var
  s:longint;
  n,b:longint;
function pd(x:longint):boolean;  //判断所获得的数值是否为素数
var
  flag:boolean;
  i:longint;
begin
  flag:=true;
  if x=1 then  flag:=flase;
        else   begin
                 for i:=2 to trunc(sqrt(x)) do
                   if x mod i=0 then  begin
                   flag:=false;
                   break;
                  end;
                end;
end;
procedure dfs(s:longint);
var
  k:longint;
begin  
  if s>n then begin writeln(b) exit end;      //完成符合位数要求素数搜索后，输出该素数
 for k:=1 to 9 do begin
      if (k=2)or(k mod 2 =1) then  begin   //要求末尾加入k值为2或者为奇数
          b:=b*10+k;    //累加位数，并把k值加入末尾，形成新的b值
if pd(b)then dfs(s+1); //判断新形成的数值是否是素数，是深度搜索下1位数值；
         s:=s-1;b:=b div 10; //恢复现场，为继续加入下一个数值初始化；
        end;
     end;
  end;
begin
  readln(n);          //读入数值的位数
  s:=1;              //统计位数
  dfs(1);            //搜索数值
end.

```

---

## 作者：丛林 (赞：0)

在看评论区的时候突然发现某大佬打表过了此题，楼下有人说打表题解审核不过，于是为什么不用一种神（dou）奇（bi）的打表方法，用两位的合法情况，来打三位的表，再打四位......反正思路较正常，只是实现略神（qi）奇（pa）。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#define maxn 1010
#define ll long long 
#define inf 1000000000+7
using namespace std;//论打表的正确方法
int a[10][40]={{0},{0,2,3,5,7},{0,23,29,31,37,53,59,71,73,79}};//打出1~2位的质数表，删去不合法的情况 
int s[10]={0,4,9};//存个数 
int n,m;
bool prime(int x)//神奇而低效的判质数方法 
{
    for(int i=2;i<=sqrt(x);i++)
        if(x%i==0)
            return false;
    return true;
}
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
int get(int x)//按位取数 
{
    for(int i=1;i<=s[x-1];i++)
    {
        for(int j=1;j<=9;j+=2)
        {
            int k=a[x-1][i]*10+j;
            if(prime(k)&&k)
                a[x][++s[x]]=k;
        }
    }
}
int main()
{
    n=read();
    for(int i=3;i<=n;i++)//开始愉快地打表 
        get(i);
    for(int j=1;j<=s[n];j++)
    {
        printf("%d\n",a[n][j]);
    }
    return 0; 
}
```

---

## 作者：欧阳锋Oliver (赞：0)

这道题我用了宽搜的思想，详见代码注释（代码格式丑勿喷）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[4]= {1,3,7,9};//每一次增添一位，只有增加1,3,7,9的数才是质数。
long long a[1000001];
bool prime(int x) {
    int i;
    for(i=2; i<=trunc(sqrt(x)); i++)
        if(x%i==0) return false;
    return true;
```
}//判断质数
```cpp
int main() {
    int f=0,r=4,len=1,i;
    a[1]=2;a[2]=3;a[3]=5;a[4]=7;//最初的四个质数
    cin>>n;
    for(i=1; i<=n-1; i++)
        len*=10;
    while(f<=r) {
        f++;
        int tmp=a[f]/len;
        if(tmp>=2&&tmp<=7) {
            cout<<a[f]<<endl;
        } 
      else if(tmp!=0) break;
      for(i=0; i<4; i++) {
            tmp=a[f]*10+d[i];
            if(prime(tmp)&&tmp/len<=7)
                a[++r]=tmp;
        }
```
}//宽搜
    return 0;

}

---

