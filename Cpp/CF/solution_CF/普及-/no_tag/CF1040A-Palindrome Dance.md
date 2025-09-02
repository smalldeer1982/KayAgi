# Palindrome Dance

## 题目描述

### 题目大意
给你一个序列，里面的元素只能是 $0,1$ 或 $2$，$2$ 可以通过代价换成 $1$ 或者 $0$，问形成**仅包含 $0,1$** 的回文串的最小代价。

## 样例 #1

### 输入

```
5 100 1
0 1 2 1 2
```

### 输出

```
101
```

## 样例 #2

### 输入

```
3 10 12
1 2 0
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 12 1
0 1 0
```

### 输出

```
0
```

# 题解

## 作者：风之城0 (赞：3)

这题其实十分简单，只要用O(n/2)扫一遍，在特判一下就可以了
，主要是注意要将一切的2转变成1或0这一点，比如：

输入：3 6 10\n2 1 2
输出：12

看似已经是回文数了，但也要将2转换，以下是代码：


```cpp
#include<cstdio>
#include<cctype>
using namespace std;
inline int read()
{int X=0,w=0;
 char ch=0;   
 while(!isdigit(ch)) 
    {w|=ch=='-';
    ch=getchar();}    
 while(isdigit(ch)) 
    {X=(X<<3)+(X<<1)+(ch^48);
    ch=getchar();}
 return w?-X:X;
}
inline int mn(int x,int y){
    return x<y?x:y;
}
int main(){
    int n,a1,b,a[21],ans=0;
    n=read();a1=read();b=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    for(int i=1;i<=int(n/2);i++){
        if(a[i]==a[n-i+1]&&a[i]==2)
            ans+=mn(a1,b)+mn(a1,b);//判断是否都为2
        if(a[i]!=a[n-i+1]){
            if(a[i]==2)ans+=(a[n-i+1]==0?a1:b);
            else if(a[n-i+1]==2)ans+=(a[i]==0?a1:b);
            else{
                printf("-1\n");//无法转换成回文数
              	return 0;
            }       	
        }
    }
    if(n%2==1&&a[n/2+1]==2)ans+=mn(a1,b);//判断n如果不能整除2，再看中间的数是否为2，然后进行转换
    printf("%d\n",ans);//输出答案
    return 0;
}

```

---

## 作者：Priori_Incantatem (赞：1)


回文数  $12321$  
它从左往右数第i位和从右往左数第i位是一样的，所以可以利用此性质创造回文数

首先特判n为奇数，其中再特判n==1的情况  
然后直接从$1$~$n/2$ 扫一遍

具体见代码:
```cpp
#include<iostream>
#include<cmath>
using namespace std;
char a[21];//序列
int n,x,y,ans;//ans为所要的代价
int main(){
    cin>>n>>x>>y;
    int i;
    for(i=1;i<=n;i++)cin>>a[i];
    if(n%2)   //如果n为奇数
    {
        if(a[n/2+1]=='2')
        {
            ans+=min(x,y);//中间的数无所谓，所以挑便宜的
            if(x<y) a[n/2+1]='0';
            else a[n/2+1]='1';
        }
        if(n==1){cout<<ans<<endl; return 0;}//如果n为1,就直接输出并结束程序
    }
    for(i=1;i<=n/2;i++)
    {
        if((a[i]=='0'&&a[n-i+1]=='1')||(a[i]=='1'&&a[n-i+1]=='0'))//如果两边不对称并且不能修改则无解
        {
        	cout<<-1<<endl;
        	return 0;
        }
        if(a[i]=='2'&&a[n-i+1]=='2')//如果两边都是2,也是挑便宜的
        {
            ans+=min(x,y)*2;
            if(x<y){a[i]=a[n-i+1]='0';}
            else a[i]=a[n-i+1]='1';
        }
        else if(a[i]=='2')//如果只能单边修改，就改成和另一边对称
        {
            if(a[n-i+1]=='1'){ans+=y;a[i]='1';}
            else {ans+=x;a[i]='0';}
        }
        else if(a[n-i+1]=='2')
        {
            if(a[i]=='1'){ans+=y;a[n-i+1]='1';}
            else {ans+=x;a[n-i+1]='0';}
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：gary2005 (赞：1)

这是一题典型的dfs

只要判断每个二换成0/1的情况就OK了

由于数据水并不会超时

**上代码！！！**

------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int huan1,huan0;//换成1的钱和换成0的钱
int n,num[25],tot2=0,weizhi2[25];int minans=2500,tempans=0;
bool panduan(){//判断回文 
	int head=1,tail=n;
	while(head<tail){
		if(num[head]!=num[tail]) return false;//不同，则不是回文 
		head++;
		tail--;
	}
	return true;
}
void dfs(int now){
	if(now==tot2+1){//边界条件 
//		for(int i=1;i<=n;i++) cout<<num[i];
//		cout<<endl;
		if(panduan()) minans=min(minans,tempans);
		return;
	}
	num[weizhi2[now]]=1;//换成1 
	tempans+=huan1;//加上代价 
	dfs(now+1);//递归下一个 
	tempans-=huan1;//回溯 
	num[weizhi2[now]]=0;//换成0 
	tempans+=huan0;//加上代价 
	dfs(now+1); //递归下一个 
	tempans-=huan0;//回溯
}
int main(){
	scanf("%d %d %d",&n,&huan0,&huan1);//输入 
	for(int i=1;i<=n;i++){
		scanf("%d",&num[i]);//输入 
		if(num[i]==2){//如果是二则记录二的位置，且二的个数++ 
			tot2++;//总数++ 
		weizhi2[tot2]=i;//记录位置 
		}
	}
	dfs(1);//从第一个2开始 
	if(minans!=2500) cout<<minans; //最小答案 
	else cout<<-1;  //无法达成回文
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 思路

我们先扫一遍整个数组 $x$，如果 $x_i$ 和 $x_{n-i+1}$ 都不等于 $2$ 的情况，直接 $\verb!continue!$，开始下一次判断，否则我们就需要分情况讨论。

- 如果 $x_i = 2$ 且 $x_{n-i+1} ≠ 2$

说明 $x_i$ 需要做出改变，那么我们只需要看看 $x_{n-i+1}$ 的值是几就行了。

如果 $x_{n-i+1} = 0$，我们就把 $x_i$ 替换成 $0$，并且统计代价的变量 $s = s + a$。

否则把 $x_i$ 替换成 $1$，并且 $s = s + b$。



- 如果 $x_{n-i+1} = 2$ 且 $x_i ≠ 2$

说明 $x_{n-i+1}$ 需要做出改变，那么我们只需要看看 $x_i$ 的值是几就行了。

如果 $x_i = 0$，我们就把 $x_{n-i+1}$ 替换成 $0$，并且 $s = s + a$。

否则把 $x_{n-i+1}$ 替换成 $1$，并且 $s = s + b$。

- 如果 $x_i = 2$ 且 $x_{n-i+1} = 2$

这样的情况比上两种稍微复杂一点，我们只需要看看 $a$ 和 $b$ 那个比较小就行了。

如果 $a<b$

说明把 $x_i$ 替换成 $0$ 的代价比较小，那么 $x_i = 0$ 且 $s = s + a$。

否则把 $x_i$ 替换成 $1$ 的代价比较小，那么 $x_i = 1$ 且 $s = s + b$。

注意我们只需要改变 $x_i$ 的值就好了，不需要改变 $x_{n-i+1}$ 的值。

最后判断一下全部改变完后的数组是否回文即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	//定义
	 
	int n,a,b,x[10001],i,s;
	
	//输入 
	cin>>n>>a>>b;
	
	//变量赋值
	 
	s = 0;
	
	//循环输入
	 
	for(i=1;i<=n;i++)
		cin>>x[i];
		
	//开始把 2 消掉 
	for(i=1;i<=n;i++)
	{
		if(x[i]==x[n-i+1]&&x[i]!=2)//如果 x[i] 和 x[n-i+1] 都不为 2  
			continue;//开始下一次的判断 
		else if(x[i]==2&&x[n-i+1]!=2)//如果 x[i] = 2 且 x[n-i+1] != 2 
		{
			if(x[n-i+1]==0)//做出把 x[i] 替换成 0 或 1 的决定。  
				s += a,x[i] = 0;
			else
				s += b,x[i] = 1;
			//记得代价变量 s 要根据 x[n-i+1] 的值做决定。 
		}
		else if(x[n-i+1]==2&&x[i]!=2)//如果 x[n-i+1] = 2 且 x[i] != 2 
		{
			if(x[i]==0)//做出把 x[n-i+1] 替换成 0 或 1 的决定。  
				s += a,x[n-i+1] = 0;
			else
				s += b,x[n-i+1] = 1;
			//记得 s 要根据 x[i] 的值做决定。
		}
		else if(x[i]==2&&x[n-i+1]==2)//如果 x[n-i+1] = 2 且 x[i] = 2 
		{
			if(a>b)//判断把 x[i] 替换成几比较合适 
				x[i] = 1,s += b;
			else
				x[i] = 0,s += a;
		}
	}
	
	//操作完毕后判断数组是否会文
	 
	for(i=1;i<=n/2+1;i++)
	{
		if(x[i]==x[n-i+1])
			;// x[i] = x[n-i+1]，继续下一次比较 
		else
			return printf("-1\n"),0;//否则不回文，输出 -1，程序结束。 
	}
	printf("%d\n",s);//回文，输出代价变量 s。 
	return 0; 
}
```



---

## 作者：j1ANGFeng (赞：0)

### 分析
将数组扫一遍，然后分类讨论：
1. 两个数一致且不为 $2$ ，直接跳过。
2. 两个数一致且为 $2$ ，加上 $ \min ( a , b ) $  的两倍。 如果 $2$ 在正中央就加上 $ \min ( a , b ) $。
3. 两个数不一致且都不为 $2$，无解。
4. 两个数不一致且有一个为 $2$，把 $2$ 变为另一个数。
### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define ll long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}
int q[N];
signed main(){
	int n=rd(),a=rd(),b=rd(),ans=0;
	for(int i=1;i<=n;++i){
		q[i]=rd();
	}
	for(int i=1,j=n;i<=j;++i,--j){
		if(q[i]==q[j]&&q[i]!=2)
		  continue;
		if(q[i]==q[j]&&q[i]==2){
			ans+=min(a,b);
			if(i!=j)
			  ans+=min(a,b);
		}
		if(q[i]!=2&&q[j]==2)
		  ans+=q[i]==0?a:b;
		if(q[i]==2&&q[j]!=2)
		  ans+=q[j]==0?a:b;
		if(q[i]!=2&&q[j]!=2){
			puts("-1");
			return 0;
		}
	}
	wt(ans);
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

# 题目分析
回文数是指从左数第 $i$ 位与从右数第 $i$ 位一致的数。       

将数组从两端扫一遍，然后分情况讨论：      
1. 两个数不一致且都不为 $2$，则无解。
2. 两个数一致且都不为 $2$，无需操作。
3. 两个数不一致且有一个数为 $2$，答案加上将 $2$ 变为另一个数所需的代价。
4. 两数都为 $2$，答案加上两种代价的最小值的 $2$ 倍。注意特判 $2$ 在正中央。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int f[25];
signed main(){
	int n=read(),a=read(),b=read();
	for(int z=1;z<=n;z++){
		f[z]=read();
	}
	int ans=0;
	for(int i=1,j=n;i<=j;i++,j--){
		if(f[i]==f[j]&&f[i]!=2) continue;//如果对应数相等且不为2，直接退出 
		if(f[i]==2&&f[j]!=2){
			ans+=f[j]==0?a:b; 
		}
		if(f[i]!=2&&f[j]==2){
			ans+=f[i]==0?a:b;
		}
		if(f[i]==2&&f[j]==2){
			ans+=i==j?min(a,b):min(a,b)*2;//注意特判i==j 
		}
		if(f[i]!=2&&f[j]!=2){//无解 
			puts("-1");
			return 0;
		}
	}
	cout<<ans;
}
```


---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1040A) | [CF 原题传送门](https://codeforces.com/problemset/problem/1040/A)

基础回文数判断题。

感觉题目翻译并不是很好，需要注意回文串中**不能**出现 $2$，例如 $1 0 2 0 1$ 不能作为最终答案。

## 思路

直接把数组从 $1$ 到 $\lfloor \frac{n}{2}\rfloor $ 扫一遍即可。

有以下几种情况需要分类讨论：

1. 如果原串首尾不同但不是 $2$，即形如 $10100$ 这样的，无法变为回文串，直接输出 $-1$；
2. 如果原串首尾都为 $2$，只需要把两个 $2$ 都换成 $0$ 和 $1$ 中**代价最小的数**；
3. 如果原串首尾有且仅有一个是 $2$，把那一个 $2$ 改为**和另一端相同的数**；
4. 最后再特判 $n$ 为奇数的情况，如果中间数为 $2$， $ans$ 需要再加上 $\min(a,b)$ 以**形成不含 $2$ 的回文串**。

然后这道题就很简单了。

## 代码

```cpp
#include<cmath>
#include<iostream>
using namespace std;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
int n,a,b,t[30],ans=0;
int main()
{
	n=read();a=read();b=read();
	for(int i=1;i<=n;i++) t[i]=read();
	for(int i=1;i<=n/2;i++)
	{
		if((t[i]==0 && t[n-i+1]==1) || (t[i]==1 && t[n-i+1]==0))//首尾不同且不是2
		{
			cout<<-1<<endl;
			return 0;
		}
		else if(t[i]==2 && t[n-i+1]==2)//首尾都为2
		{
			ans+=min(a,b)*2;
			if(a<b) t[i]=t[n-i+1]=0;
			else t[i]=t[n-i+1]=1;
		}
		else if(t[i]!=2 && t[n-i+1]==2)//结尾为2
		{
			if(t[i]==0) ans+=a,t[n-i+1]=0;
			else ans+=b,t[n-i+1]=1;
		}
		else if(t[i]==2 && t[n-i+1]!=2)//开头为2
		{
			if(t[n-i+1]==0) ans+=a,t[i]=0;
			else ans+=b,t[i]=1;
		}
	}
	if(n%2==1 && t[n/2+1]==2) ans+=min(a,b);//n为奇数需要特判
	cout<<ans<<endl;
	return 0;
}
```

---

