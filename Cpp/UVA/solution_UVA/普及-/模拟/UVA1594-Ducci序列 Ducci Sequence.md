# Ducci序列 Ducci Sequence

## 题目描述

对于一个 $n$ 元组（$a_1,a_2,\cdots,a_n$），可以对每个数求出它和下一个数的差的绝对值，得到一个新的 $n$ 元组（$|a_1-a_2|,|a_2-a_3|,\cdots,|a_n-a_1|$）。重复这个过程，得到的序列称为 Ducci 序列，例如：

$$(8,11,2,7)\rightarrow(3,9,5,1)\rightarrow(6,4,4,2)\rightarrow(2,0,2,4)\rightarrow(2,2,2,2)\rightarrow(0,0,0,0)$$

也有的 Ducci 序列最终会循环。输入 $n$ 元组（$3\le n\le15$），你的任务是判断它最终会变成0还是会循环。输入保证最多 $1000$ 步就会变成 $0$ 或循环。

## 样例 #1

### 输入

```
4
4
8 11 2 7
5
4 2 0 2 0
7
0 0 0 0 0 0 0
6
1 2 3 1 2 3
```

### 输出

```
ZERO
LOOP
ZERO
LOOP
```

# 题解

## 作者：StayAlone (赞：9)

### 题意

给定一个长度为 $n$ 的数组 $a$，每一次变化是指将 $a$ 数组的值改为 $|a_1 - a_2|, |a_2 - a_3|, |a_3 - a_4|, \cdots, |a_n - a_1|$。已知该数组最后会陷入一个循环或 $a_1 = a_2 = a_3 = \cdots = a_n = 0$，且其特征一定会在 $1000$ 次变化结束之前显现出来。若陷入循环，输出 ``LOOP``，否则输出 ``ZERO``。  

有 $t$ 组测试数据。

### 思路

直接模拟每一次操作之后的 $a$ 数组的情况，拿一个 $flag$ 来存储是否出现全为 $0$，如果出现全部为 $0$ 的情况，$flag$ 标为 $\texttt{true}$，如果 $1000$ 次之后没有出现全部为 $0$ 的情况，输出 ``LOOP``。  

这里有一个细节：**为什么不判断陷入循环而要判断全部为 0 呢？**  
因为判断全部为 $0$ 不需要额外写很多东西，一个函数即可，而判断陷入循环需要再拿一个数组存开始的值。  

现定义 $de$ 函数，该函数将会把数组 $a$ 进行题目中的一次处理。实现只需要从 $1$ 枚举到 $n-1$，每一次 $a_i = |a_i - a_{i+1}$|，而 $a_n$ 的处理比较特殊：要在 $a_1$ 变化前拿一个变量 $a1$ 存储它的值，最后 $a_n = |a_n - a1|$。

```cpp
void de()
{
	int a1 = a[1];
	for (int i = 1; i < n; ++i) a[i] = abs(a[i] - a[i+1]);
	a[n] = abs(a[n] - a1);
}
```

接下来就是模拟 $1000$ 次，每一次处理后判断是否全为 $0$。  
```cpp
bool zero(int *ar)
{
	for (int i = 1; i <= n; ++i)
		if (ar[i]) return false; // 如果出现一个不为 0 的值，返回 false
	return true;
}
```

如果判断出来全部为 $0$，则将 $flag$ 标记为 $\texttt{true}$ 并 $\texttt{break}$。  

最后如果 $flag$ 为 $\texttt{true}$，输出 ``ZERO``，否则输出 ``LOOP``。  

[AC code记录](https://www.luogu.com.cn/record/51132326)
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[20]; bool f;
void de()
{
	int a1 = a[1];
	for (int i = 1; i < n; ++i) a[i] = abs(a[i] - a[i+1]);
	a[n] = abs(a[n] - a1);
}

bool zero(int *ar)
{
	for (int i = 1; i <= n; ++i)
		if (ar[i]) return false;
	return true;
}

int main()
{
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n); f = false;
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= 1000; ++i)
		{
			de();
			if (zero(a))
			{
				f = true; break;
			}
		}
		puts(f ? "ZERO" : "LOOP");
	}
	return 0;
}
```
## 彩蛋(必看)

![](https://cdn.luogu.com.cn/upload/image_hosting/kljt6tk4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
``
We get our cycle in 50 steps if we are to get. But why? I just gave up. Please let me know if you find out.
``

简单说就是，其实你模拟 $50$ 次就可以 AC ~~，因为数据水~~。  
然后我就拿到了目前最优解榜1，无 O2。当然，我相信这件事现在大家一知道就极有可能快于我。  

[数据水的AC code记录](https://www.luogu.com.cn/record/51165507)

---

## 作者：jimmyzzt (赞：5)

##### 这题我认为，直接模拟就行了
  
  唯一需要注意的是要利用好题目所给的一切信息，题目中提到 _输入保证最多1000步就会变成 0或循环。_ 那我们大可不判断是否循环，直接操作100次，只要没变成0，那就是循环了。这一点是比较巧妙的。
  
  话不多说上代码
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[16],temp[16],n,t,tot;
bool flag;
void ope()//为了使主程序简洁，故把每次操作用一个函数来完成
{
	for(int i=1;i<=n;i++)
	{
		if(i!=n) temp[i]=abs(a[i]-a[i+1]);
		else temp[i]=abs(a[i]-a[1]);
	}
	for(int i=1;i<=n;i++) a[i]=temp[i];
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		tot=1000;
		while(tot--)
		{
			ope();
			flag=true;
            //其实不用立flag的，直接判tot==0就ok，但莫名wa掉了QAQ
			for(int i=1;i<=n && flag;i++)
            	if(a[i]!=0) flag=false;
			if(flag)
			{
				printf("ZERO\n");
				break;
			}
		}
		if(!flag) printf("LOOP\n");//一千次仍不是0，就是循环了
	}
	return 0;
}
```

---

## 作者：GVNDN (赞：3)

~~这是我UVA上AC的第一道题！！~~

对不起大家呀，在看书的时候看走眼了，以为这题建议用vector写，就硬着头皮这样写了，用数组明显更方便。

判断循环的思路就是将计算后得出的新元组通过map（就是代码中的tid；叫做tid是因为本来想给每个新元组分配一个id，后来发现没必要，但名字就懒得改了）进行记录，如果新元组在map中已经存在，就判定为循环。

当然也可以不判断是否循环，直接进行1000次变换后判断是否为全零元组即可（参见最高赞题解）。
用map存储元组映射有可能会导致速度较慢，但count方法用起来挺方便的。

纯新手，请大家多包涵！
```cpp
#include<iostream>
#include<vector>
#include<map>
#include<cmath>
using namespace std;
int main()
{
    int n, T;
    cin >> T;
    while(T--)
    {
    	vector<int> tup;
    	map<vector<int>, int> tid;    //记录已经出现过的元组
        cin >> n;
        vector<int> z(n, 0);    //全零vector
        for(int i = 0; i < n; i++)
        {
        	int a;
        	cin >> a;
        	tup.push_back(a);
        }
        while(1)
        {
        	vector<int> tup2;
            for(int i = 0; i < n; i++)
            {
                if(i == n - 1) tup2.push_back(abs(tup[i] - tup[0]));
                else tup2.push_back(abs(tup[i] - tup[i+1]));
            }
            if(tid.count(tup2)) {cout << "LOOP" << endl; break;}
            else if(tup2 == z) {cout << "ZERO" << endl; break;}
            else tid[tup2] = 1;
            tup = tup2;
        }
    }
    return 0;
}
```

---

## 作者：XKqwq (赞：2)

### $\texttt{Key}$

题目已说明：

> 输入保证最多 $1000$ 步就会变成 $0$ 或循环。

那么可以理解为：

> 无论 $1000$ 步完成之前怎样，$1000$ 步后只有两种情况：全为 $0$ 或循环。

所以很容易想到直接模拟 $1000$ 次，然后判断是否全为 $0$,如果是，答案就是`ZERO`,如果不是，答案就是`LOOP`。

### $\texttt{Code}$

附带详细注释，极为详细。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool all_zero(int n,int a[]){ // 判断 a 数组是否全部为零 
	for(int i=0;i<n;i++) if(a[i]!=0) return false; 
	// 遇到非 0 直接返回，不需要考虑后面 
	return true; // 能执行到这里就是全为零   
}
void solve(int n,int a[]){  
	int t=1;
	for(;t<=1000;t++){  // 执行 1000 次 
		for(int i=0;(i<n);i++) a[i]=abs(a[i]-a[i+1]); // 按题意计算就行，记得是绝对值 
		// 见主函数里的解释 
		// 不需要特判 
		a[n]=a[0]; //【注意】 每次都要存一下 
	}
	// 这里不返回，直接输出 
	// puts() 函数专门用于输出字符串，会换行 
	if(all_zero(n,a)) puts("ZERO"); // 返回 true 全为零 
	else puts("LOOP"); //  
}
int T,n,a[20];   
int main(){
	cin>>T;  
	while(T--){
		cin>>n;
		for(int i=0;i<n;i++) cin>>a[i];
		a[n]=a[0]; 
		// 这里提取出 a[0] ，因为 a[n] 的计算会用到
		//而如果正常计算，a[0] 的值一开始就会改变。
		//关于为什么用 a[n] ：我的输入是从下标 0 开始，不会用到 n 
		//当然可以再定义一个变量，不过为了方便处理，就这样了
		//如果习惯下标从 1 开始，可以用 a[0]  
		solve(n,a);
	}
	return 0;
}
//AC 
```





---

## 作者：mcDinic (赞：2)

## 常规解法：

这题，如果要把 STL 套进去，那么方法很简单（~~也很烦~~），就是开个 map，统计某种状态出现的次数，如果当前状态全是 0，结束，如果当前状态出现了 2 次，也结束。

### 问题及解决方法：

如何记录当前的状态，是最大的问题。

这时，我们想到，如果把所有数拼起来，所形成的那个数不就能表示状态了吗？只不过那个数太大了，得用字符串表示，所以数组要变为字符串，一切计算要用高精度（不这样也行，可以每次拼字符串前转换一下）。

### Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
string a[105],op;//a 为当前各元素值，op 为每步高精减的结果。
map<string,int>mp;//记录状态。
void jian(string x,string y){//技艺不行，啰里啰唆打了一大堆。
	string _1,_2;
	_1.clear();_2.clear();
	for(int i=0;i<x.size();i++){
		_1+=x[x.size()-1-i];
	}
	for(int i=0;i<y.size();i++){
		_2+=y[y.size()-1-i];
	}//反序排列。
	if(_1.size()>_2.size()){
		for(int i=_2.size();i<=_1.size()-1;i++)_2+='0';
	}
	if(_2.size()>_1.size()){
		for(int i=_1.size();i<=_2.size()-1;i++)_1+='0';
	}//位数补一样。
	int w=0;
	for(int i=_1.size()-1;i>=0;i--){
		if(_1[i]<_2[i]){
			swap(_1,_2);
			w=1;
			break;
		}
		if(_1[i]>_2[i]){
			w=1;
			break;
		}
	}//确定被减数。
	if(w==0){
		op+='0';
		return;
	}
	int noi=0;
	string akioi;
	for(int i=0;i<_1.size();i++){
		int yu;
		if(_1[i]-_2[i]-noi<0){			
			yu=_1[i]-_2[i]-noi+10;
			akioi[i]=(char)(yu+48);
			noi=1;
		}
		else{
			yu=_1[i]-_2[i]-noi;
			akioi[i]=(char)(yu+48);
			noi=0;
		}
	}//计算。
	int t=_1.size()-1;
	for(int i=_1.size()-1;i>=0;i--){
		if(akioi[i]!='0')break;
		t--;
	}//删前导 0。
	for(int i=t;i>=0;i--){
		op+=akioi[i];
	}
	return;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		mp.clear();
		op.clear();
		string s,ans;//s 为每步状态，ans 为目标值（全为 0）。
		s.clear();ans.clear(); 
		for(int i=1;i<=n;i++){
			cin>>a[i];
			s+=a[i];
			ans.resize(i);
			ans[i-1]='0'; 
		}
		mp[s]=1;
		for(int i=1;i<=1100;i++){
			if(mp[ans]==1){
				cout<<"ZERO\n";
				break;
			}
			s.clear();
			string xpp=a[1];
			for(int j=1;j<n;j++){
				op.clear();
				jian(a[j],a[j+1]);
				a[j]=op;
				s+=a[j];
			}
			op.clear();
			jian(a[n],xpp);
			a[n]=op;
			s+=a[n];
			mp[s]++;
			op.clear();
			if(mp[s]>1){
				cout<<"LOOP\n";
				break;
			}
		}
	}
    return 0;	
}
```

## 更优解法：

刚刚那个程序，大家也看到了，那么长，虽说本人技艺不行，但即使浓缩，仍需打很多。这里说个更优解。

因为题目中说，输入保证最多 1000 步就会变成 0 或循环。倘若无视“循环”二字，那么我们就可以理解为：若会变成 0，最多 1000 步就会出结果。

反过来理解，这不就是说：**1000 步内不变成 0，那么就永远不会变成 0。**

所以，我们就可以只考虑变成 0 的情况，而不用管循环的情况了。

### Code：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[105];
bool pd(){
	for(int i=1;i<=n;i++){
		if(a[i]!=0)return 0;
	}
	return 1;
}//判断是否全为 0。
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int w=0;
		for(int i=1;i<=1000;i++){
			if(pd()){
				w=1;
				cout<<"ZERO\n";
				break;
			}
			int xpp=a[1];
			for(int j=1;j<n;j++){
				a[j]=abs(a[j+1]-a[j]);
			}
			a[n]=abs(a[n]-xpp);
		}
		if(w==0){
			cout<<"LOOP\n";
		}
	}
    return 0;	
}
```

## 尾声：

好了，本篇题解讲完了，2 份代码没挖坑，放心食用吧！

---

## 作者：CQ_Bab (赞：1)

## 思路
这道题暴力可以直接过，所以我们直接暴力，只需要暴力 $1000$ 次即可，我们直接用一个函数来变（定义一个数组，每次 $i\ne n$ 就将 $b_i=a_i-a_{i+1}$ 否则 $b_i=a_n-a_i$。然后将 $a$ 复制成 $b$ 数组）。然后循环遍历判断是否为零，如果为零就输出 $\texttt{ZERO}$ 并结束这一次循环。如果 $1000$ 次后都没结束就输出 $\texttt{LOOP}$。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000;
int t,n,a[16];
bool f;
void fun(){
	int b[16]={0};
	for(int i=1;i<=n;i++){
		if(i!=n) b[i]=abs(a[i]-a[i+1]); // 特判 
		else b[n]=abs(a[n]-a[1]);
	}
	for(int i=1;i<=n;i++) a[i]=b[i]; // 交换 
}
int main(){
	cin>>t; // 输入 
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		int NN=1000;
		while(NN--){
			fun(); // 进行变化 
			f=false;
			for(int i=1;i<=n;i++){
				if(a[i]!=0) {
					f=true;
				}
			}
			if(!f) { // 如果全是零 
				puts("ZERO");
				break; // 退出循环 
			}
		}
		if(f) puts("LOOP"); // 输出 
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

```
这题直接用数组模拟会好一点，快的飞起

#include<cstdio>

class Solver{
public:
	int abs(int a){//绝对值
		return (a < 0) ? -a : a;
	}
	
	bool isZero(int len,int A[]){//判断是否为全0
		for(int i = 0;i < len;++i){
			if(A[i]){
				return false;
			}
		}
		return true;
	}
	
	void solve(int len,int A[]){//解题
		for(int c = 0;c < 1000;c++){//因为最多一千步，那就循环一千次
			int delta[15];//临时数组
			for(int i = 0;i < len;++i){//按题生成
				delta[i] = abs(A[i % len] - A[(i + 1) % len]);
			}
            
			for(int i = 0;i < len;++i){//赋值回去
				A[i] = delta[i];
			}
            
			if(isZero(len,A)){//判0
				printf("ZERO\n");
				return;
			}
		}
		printf("LOOP\n");
	}
	
	void main(){//输入和解题
		int A[15];
		int len;
		scanf("%d",&len);
		for(int i = 0;i < len;i++){
			scanf("%d",&A[i]);
		}
		
		solve(len,A);
	}
};

int main(){//总输入和解题
	int n;
	scanf("%d",&n);
	for(int i = 0;i < n;i++){
		(new Solver) -> main();
	}
	
	return 0;
}
```

---

## 作者：OoXiao_QioO (赞：0)

# 前言

简单模拟题。

# 题意

$t$ 组数据，每组数据输入 $n$ 和 $a$ 数组，循环 $1000$ 次，每一次更新 $a$ 数组为 $a_i$ 与 $a_{i+1}$ 的差的绝对值，即 $a_i = |a_i-a_{i+1}|$，问 $1000$ 次操作后能否让 $a$ 数组全部为 $0$。

# 思路

对于每组数据，我们先模拟个 $1000$ 次，对于每一次循环，定义一个 $b$ 数组，每一次的 $b_i$ 都为 $a$ 数组中相邻两个数的差的绝对值，所以 $b_i = |a_i-a_{i+1}|$。

但是第 $n$ 个数的时候呢？通过研究样例，发现 $b_n$ 为 $|a_n-a_1|$，更新完 $b$ 数组，比对一下是否都为 $0$ 即可。

提交上去，结果 $\verb!TLE!$ 了，考虑优化。

发现模拟 $1000$ 次实在是太浪费空间了，我们根据~~人类心理学~~概率学考虑一下，发现数据的强度使正正好好 $1000$ 次模拟后数组全为 $0$ 的几率还是太小了，最多大约是在 $70$ 左右，于是模拟 $70$ 次就可以了。

# 代码（核心部分）

```cpp
while(t--)
{
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i];
	for(i=1;i<=70;i++)//模拟 70 次足矣。 
	{
		for(j=1;j<n;j++)
			b[j] = abs(a[j]-a[j+1]);//b 数组储存相邻两个数的差的绝对值。 
		b[n] = abs(a[n]-a[1]);
		for(j=1;j<=n;j++)
			a[j] = b[j];//把 b 数组复制到 a 数组。 
		f = 1;//假设全为 0。 
		for(j=1;j<=n;j++)
		{
			if(a[j])//有一个数不符合，直接跳出循环、 
			{
				f = 0;
				break;
			}
		}
		if(f)
		{
			puts("ZERO");
			break;
		}
	}
	if(!f)
		puts("LOOP");
}
```


---

## 作者：AlicX (赞：0)

此题乃是一道模拟题，认真模拟即可。

### 思路

写一个返回值为 bool 的函数，参数设为一个数组 $a$，用来记录每次的状态，次数 $k$，当 $k$ 大于等于 $1000$ 时，便返回 false，如若在途中将数组更新为了全是 $0$ 的情况，便返回 true，写一个函数实现即可，具体看代码。

AC code


```cpp
#include<bits/stdc++.h>
#define int1 long long 
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=20;
int n;
int a[N];
bool work(int a[],int k){
	if(k>=1000) return false;//超过了1000次，大于等于1000是因为k从0开始 
	int t[20];//中转数组 
	memset(t,0,sizeof t);//初始化 
	for(int i=1;i<n;i++) t[i]=abs(a[i]-a[i+1]);//计算，t[i]等于a[i]和a[i+1]的绝对值 
	t[n]=abs(a[1]-a[n]);//特判t[n] 
	bool flag=true;
	for(int i=1;i<=n;i++){
		a[i]=t[i];//将t中的值赋给a 
		if(a[i]&&flag) flag=false;//如果a[i]不为0，flag=flase（不成立） 
	}
	if(flag) return true;//a数组已经为0了 
	return work(a,k+1);//继续向下搜索 
}
signed main(){
	int T;
	cin>>T;//T组数据 
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];//读入a 
		if(work(a,0)) cout<<"ZERO"<<endl;//在1000次中a数组变为了0 
		else cout<<"LOOP"<<endl;//否则失败了 
	}
	return 0;
}
```
$$Thanks$$

---

## 作者：封禁用户 (赞：0)

[UVA1594 Ducci序列 Ducci Sequence](https://www.luogu.com.cn/problem/UVA1594)

~~**标签只有模拟，那肯定要用模拟了呀**~~

因为其它题解也讲得很详细了，所以我就提几个要注意的点：

一、$b$ 数组更新值时要注意第 $n$ 个数。

二、若不循环时输出后一定要加 ```break``` 。

三、输出内容不要**打错**。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 114514
#define ll long long
#define re register
#define in inline
ll t,n,a[N],b[N]; //开 15 就够了 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(re int i=1;i<=n;i++) cin>>a[i];
		memset(a,0,sizeof(0));
		memset(b,0,sizeof(0));
		bool flag;
		for(re int k=1;k<=1000;k++){
			for(re int i=1;i<n;i++) b[i]=abs(a[i]-a[i+1]);
			b[n]=abs(a[n]-a[1]); // !!!
			for(re int i=1;i<=n;i++) a[i]=b[i];
			flag=true;
			for(re int i=1;i<=n;i++)
			if(a[i]) flag=false; 
			if(flag){
				cout<<"ZERO"<<endl; // !!!
				break; // !!!
			} 
		}
		if(!flag) cout<<"LOOP"<<endl; //!!!
	}
	return 0;
}
```


---

## 作者：RBI_GL (赞：0)

## 题意

有一个有 $n$ 个元素的数组，每次操作将其中的每一个数变为它和下一个数的差的绝对值。判断在经过 $1000$ 次操作后，数组中的元素是否会全变为 $0$。

## 思路

模拟这 $1000$ 次操作。每一次操作用替身数组更新原数组的值，再将原数组更新为替身数组中的值，最后如果全变为 $0$，就输出 ```ZERO```，否则输出 ```LOOP```。

注意题目多测。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n;
int a[20], b[20]; // b 数组为替身数组 
int main() {
	cin >> T;
	while(T--) {
		scanf("%d", &n);
		bool ok;
		for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
		for(int j = 1; j <= 1000; ++j) {
			for(int i = 1; i <= n; ++i) { // 进行一次操作 
				if (i != n) b[i] = abs(a[i] - a[i + 1]);
				else if (i == n) b[i] = abs(a[i] - a[1]);
			}
			for(int i = 1; i <= n; ++i) a[i] = b[i]; // 将 a 数组更新 
			ok = 1; // 判断是否全为 0 
			for(int i = 1; i <= n; ++i) {
				if (a[i] != 0) ok = 0;
			}
			if (ok) {
				puts("ZERO");
				break;
			}
		}
		if (!ok) puts("LOOP");
	}
	return 0;
}
```


---

## 作者：iorit (赞：0)

[原题](https://www.luogu.com.cn/problem/UVA1594)

简单模拟

值得~~压行~~注意的是an和a1的减法

从头到尾扫的话an-a1时a1的值已经被改变

那我们就可以一开始把a1的值存到an+1

### 代码

```cpp
// 此处应有头文件
int n,t;
int a[20];
bool check() // 检测是否全0
{
	for(int i = 1;i <= n;i++)
		if( a[i] )
			return false;
	return true;
}
int main()
{
    cin >> t;
    while(t--)
    {
    	cin >> n;
    	for(int i = 1;i <= n;i++)
    		cin >> a[i];
    	int k = 1e3; // 1000
    	while(--k)
    	{
    		a[n + 1] = a[1];
    		for(int i = 1;i <= n;i++)
    			a[i] = abs( a[i] - a[i + 1] );
    		if( check() )
    			break;
		}
		if(!k)
			puts("LOOP");
		else
			puts("ZERO");
	}
    return 0;
}
```


---

## 作者：WanderingTrader (赞：0)

这题是紫书上讲完STL后的一道习题。本来还真以为要用到STL，结果发现……模拟就行了。
### 题目分析
题目中说，$n\le15$，而且如果答案是`ZERO`，1000次以前一定会全0。  
那干脆直接模拟1000次好了，每次复杂度$O(n)$，根本不可能超时。
### 代码
初始化：
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#define N 20
int a[N];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n;
		scanf("%d",&n);
		for(int i = 1;i <= n;++i)
			scanf("%d",a+i);
	}
	return 0;
}
```
循环1000次，每次按照题意将两数的差取绝对值。注意整条链算完后，a[1]的值已经变了，无法满足a[n]的计算需求，所以算之前要存一下。
```cpp
for(int i = 1;i <= 1000;++i)
{
	int x = a[1];
	for(int j = 1;j < n;++j)
		a[j] = abs(a[j] - a[j+1]);
	a[n] = abs(a[n] - x);
}
```
然后用一个flag=1（定义在1000次循环外面），如果看到有非零数，flag=0退出。  
如果跑完一遍后flag=1，退出1000次的循环。  
循环外面，如果flag=1，输出`ZERO`，否则（1000次没有一次是全0），输出`LOOP`。  
```cpp
bool flag = 1;
for(int i = 1;i <= 1000;++i)
{
	int x = a[1];
	for(int j = 1;j < n;++j)
		a[j] = abs(a[j] - a[j+1]);
	a[n] = abs(a[n] - x);
	flag = 1;
	for(int j = 1;j <= n;++j)
		if(a[j])
		{
			flag = 0;
			break;
		}
	if(flag) break;
}
if(flag) printf("ZERO");
else printf("LOOP");
printf("\n");
```
是不是很简单？  
有的时候，数据范围真的很小，那么暴力模拟也是个不错的方法(比如[P1024](/problem/P1024))。

$$
\mathrm{The\ End.}
$$

---

