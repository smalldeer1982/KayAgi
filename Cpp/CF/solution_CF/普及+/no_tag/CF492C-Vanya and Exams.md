# Vanya and Exams

## 题目描述

Vanya wants to pass $ n $ exams and get the academic scholarship. He will get the scholarship if the average grade mark for all the exams is at least $ avg $ . The exam grade cannot exceed $ r $ . Vanya has passed the exams and got grade $ a_{i} $ for the $ i $ -th exam. To increase the grade for the $ i $ -th exam by 1 point, Vanya must write $ b_{i} $ essays. He can raise the exam grade multiple times.

What is the minimum number of essays that Vanya needs to write to get scholarship?

## 说明/提示

In the first sample Vanya can write 2 essays for the 3rd exam to raise his grade by 2 points and 2 essays for the 4th exam to raise his grade by 1 point.

In the second sample, Vanya doesn't need to write any essays as his general point average already is above average.

## 样例 #1

### 输入

```
5 5 4
5 2
4 7
3 1
3 2
2 5
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 5 4
5 2
5 2
```

### 输出

```
0
```

# 题解

## 作者：donotctjuntilAFO (赞：2)

# 本题算法：贪心

### 算法：

我们要求最少需要写的论文数量，那么可以使用贪心算法。

先挑最容易得分的学科开始写，所以我们可以先将各学科按需写的论文数排序。

先求出总分，然后不断减掉，直到等于零为止。

### 注意事项：

1. 如果一开始的已得分超过总分时直接输出 $0$ 。

2. 每一门分数不能超过 $r$ 。

3. 开 ` long long ` 。

代码：

```cpp
#include<bits/stdc++.h>
#define f(i,l,r) for(int i=l;i<=r;++i)
#define F(i,r,l) for(int i=r;i>=l;--i)
#define LL long long
#define ULL unsigned long long
using namespace std;
LL n,r,avg,ans,cur;
struct node{
    LL a,b;
    bool operator<(const node &x){
        return this->b<x.b;
    }
}t[100005];
int main(){
    scanf("%lld%lld%lld",&n,&r,&avg);
    cur=n*avg;
    f(i,1,n){
        scanf("%lld%lld",&t[i].a,&t[i].b);
        if(cur>t[i].a){
            cur-=t[i].a;
        }
        else{
            printf("0");
            return 0;
        }
    }
    sort(t+1,t+n+1);
    LL now=1;
    while(cur>=r-t[now].a&&now<=n){
        ans+=(r-t[now].a)*t[now].b;
        cur-=r-t[now].a;
        now++;
    }
    ans+=cur*t[now].b;
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：YanYou (赞：2)

# 贪心水题！

博客中食用，体验更好哦：
**[YanYou ’s blog](https://www.luogu.org/blog/YanYou/solution-cf492c)**

-----------------------------------------------------------

## Solution

题目让我们求最少需要写的论文数量，那么显然是挑得分最容易的学科写，因此我们可以先将各学科按需写的论文数排序。

然后从头扫到尾，直至平均分达到要求。

**注意：** 判断平均分时，不要每次计算，先求出总分，在不断减掉，直到等于零。

-----------------------------------------------------------

## Code

好啦，下面是代码。

```pascal
var n,m,ave,i:longint;
    s,ans:int64;
    a,b:array[0..100010] of longint;
procedure sort(l,r:longint);//快排（P党的悲催啊）
var i,j,m1,m2,t:longint;
begin
  i:=l; j:=r; m1:=b[(l+r) shr 1]; m2:=a[(l+r) shr 1];
  repeat
    while (b[i]<m1)or(b[i]=m1)and(a[i]<m2) do inc(i);
    while (m1<b[j])or(m1=b[j])and(m2<a[j]) do dec(j);
    if i<=j then begin
      t:=a[i]; a[i]:=a[j]; a[j]:=t;
      t:=b[i]; b[i]:=b[j]; b[j]:=t;
      inc(i); dec(j);
    end;
  until i>j;
  if l<j then sort(l,j);
  if i<r then sort(i,r);
end;
begin
  readln(n,m,ave); s:=n*ave;
  for i:=1 to n do begin
    readln(a[i],b[i]);
    dec(s,a[i]);
  end;
  if s=0 then begin writeln(0); exit; end;//判断是否需要写论文
  sort(1,n);
  i:=1;
  while s>0 do begin
    if m-a[i]<=s then inc(ans,b[i]*(m-a[i]))
    else inc(ans,s*b[i]);//尽量写代价低的（即得一分需写的论文少的）
    dec(s,(m-a[i]));
    inc(i);
  end;
  writeln(ans);
end.
```


---

## 作者：NotNaLocker (赞：2)

### 提交前の提示：
- 论文数之大，```int``` 放不下。

- 特判总学分，如果大于 $avg \cdot n$，直接输出 $0$。

### 题目思路：
**贪心+结构体排序**。要想论文数最少，当然以论文的数量来排序。如果论文数量相等的话，就以原学分越高的排前。于是排序的部分就是这样：
```cpp
bool cmp(subject a,subject b){
	if(a.b<b.b) return 1;
	else if(a.b==b.b&&a.a>b.a) return 1;
	else return 0;
}
```
接着就是模拟写论文。我们可以用一个 $sum$ 变量来计算原学分加上写论文增加的学分，如果 $sum$ 超过了 $avg \cdot n$ 也就是总值，那么直接退出循环即可。

（代码里有更详细的解释）
```cpp
int i=1;
	while(sum<avg*n){
		if(avg*n-sum>r-vanya[i].a){   //学分仍然不够达到要求，就加学分，同时累计sum。
			ans+=vanya[i].b*(r-vanya[i].a);   //注意，这里要乘以论文数，如果直接加的话那论文数这个值就没什么用了。
			sum+=r-vanya[i].a;
			i++;
		}
		else{   //最后一次，直接加完学分后退出循环。
			ans+=vanya[i].b*(avg*n-sum);
			break;
		}
	}
```
# Code:
~~你们最期待的环节来了~~
```cpp
#include<bits/stdc++.h>
#define ll long long   //记住开long long。
using namespace std;
ll n,r,avg,sum,ans;
struct subject{
	ll a,b;
}vanya[100005];   //结构体排序更方便。
bool cmp(subject a,subject b){
	if(a.b<b.b) return 1;
	else if(a.b==b.b&&a.a>b.a) return 1;
	else return 0;
}
int main(){
	cin>>n>>r>>avg;
	for(int i=1;i<=n;i++){
		cin>>vanya[i].a>>vanya[i].b;
		sum+=vanya[i].a;
	}
	if(sum>avg*n){   //特判，原因如题解顶部要求
		cout<<"0";
		return 0;
	}
	sort(vanya+1,vanya+n+1,cmp);
	int i=1;
	while(sum<avg*n){
		if(avg*n-sum>r-vanya[i].a){
			ans+=vanya[i].b*(r-vanya[i].a);
			sum+=r-vanya[i].a;
			i++;
		}
		else{
			ans+=vanya[i].b*(avg*n-sum);
			break;
		}
	}
	cout<<ans;
	return 0;   //不那么华丽的收尾
}

```
### Thanks for watching.

---

## 作者：Randolph、 (赞：1)

## [CF492C Vanya and Exams](https://www.luogu.org/problem/CF492C)

~~有了Pascal题解，来一波C++题解呀qwq。。~~

简单的贪心题

按b[i]从小到大排序，一个一个学科写直到达到要求即可

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct number {
	long long a,b;
	bool operator <(const number &x)const {
		return b<x.b;
	}
} a[100005];
long long ans,sum,n,r,ave;//不开long long最后一个点WA
int main() {
	scanf("%lld%lld%lld",&n,&r,&ave),sum=n*ave;//总共需要的学分
	for (int i=0; i<n; i++) scanf("%lld%lld",&a[i].a,&a[i].b),sum-=a[i].a;
	if (sum<=0) {//若当前学分已大于大于所需，直接输出
		puts("0");
		return 0;
	}
	sort(a,a+n);//按a[i].b排序
	for (int i=0; sum>0 && i<n; i++) {
		ans+=a[i].b*min(sum,r-a[i].a);//每个学科的论文要么尽量写完（最多只能赚r-a[i].a个学分），要么写到达到要求即可
		sum-=(r-a[i].a);//减去写论文所得学分
	}
	printf("%lld",ans);
}
```


---

## 作者：ice_fish01 (赞：1)

## $\text{CF492C Vanya and Exams}$ 题解

$\text{Update 2023.1.11}$ 

- 增加了 `#define int long long` 的原因及注意事项；

- 改正了「公式/英文/数字/汉字」与中文标点符号之间添加空格的问题；

- 改进了代码中的注释“喧宾夺主”的问题；

- 改进了一些地方的表述。

**麻烦审核本题解的管理员大大帮忙一次性找出所有问题，这样可以减少您的工作量，谢谢！**

------------

## 本题算法：贪心。

### 思路：

我们可以先用 `sort` 给这些科目进行排序，要求是加 $1$ 学分写论文数少的在前，多的在后。

然后我们就让 Vanya 同学自己一个个去写论文就行，记得别让他写得太多。

### 本题坑点：
1、不要忘记**特判**输出 `0` 的情况！

2、每门课程他**最多获得 $r$ 学分**！

3、**论文数量之大，`int` 类型存不下。论文数最高可有约 $10^{13}$ 篇**，所以要记得 `#define int long long` （即：将程序中所有的 `int` 改为 `long long`。这里需要注意的是，`main` 函数必须是 `int` 类型，所以改成 `signed main()`，它等同于 `int main()`），不然很容易找了 $30$ 分钟依旧找不到错误！！

### $\text \color{green}{AC}$ $\text \color{green}{Coding}$

```cpp
#include <bits/stdc++.h>
#define int long long //将int全部换成long long以防止数据溢出 
using namespace std;
int n,r,avg,sum; 
struct sub{
	int a,b;
}s[100010]; //把每一个科目的有关信息存在结构体中  
bool cmp(sub x,sub y)  
{
	if(x.b != y.b)
		return x.b < y.b;
	return x.a < y.a;
}
signed main()
{
	cin >> n >> r >> avg;
	for(int i = 1;i <= n;i++)
	{
		cin >> s[i].a >> s[i].b;
		sum += s[i].a; //计算总和以应对输出0的情况 
	}
    if(sum >= avg * n) //特判0的情况 
    {
    	puts("0");
    	return 0;
	}
	sort(s+1,s+n+1,cmp); //排序 
	int y = -(sum - avg * n);
	int ans = 0;
	for(int i = 1;i <= n;i++)
	{
		if(y <= r - s[i].a) //写最后一科的论文
		{
			ans += s[i].b * y;
			break;
		}
		else //剩余论文数大于等于1科
		{
			ans += s[i].b * (r - s[i].a);
			y -= r - s[i].a;
		}
	}
	cout << ans; 
    return 0;
}

```

### 感谢管理员 [@Maxmilite](https://www.luogu.com.cn/user/274993) 对本题解提出的建议。

---

## 作者：little_cindy (赞：0)

此题考察算法：$\colorbox{red}{\color{white}\text{贪心}}$

## 思路

首先，我们可以知道，我们需要的总学分是 $avg\times n$，已经有了的学分是 $\sum\limits^{n}_{i=1}a_i$，所以，我们还需要的学分是 $avg\times n-\sum\limits^{n}_{i=1}a_i$。

问题来了，我们怎样可以使得需要的论文总数最小呢？

很显然，$b_i$ 越小，就可以用更少的论文去获得更多的分。

所以我们可以先按 $b$ 数组把每对 $a_i,b_i$ 从小到大排一遍。

为了统计需要写的论文数，我们可以用一个循环。

我们假定当前循环的下标 $i$，剩余学分为 $cha$，则当前可获得 $r-a_i$ 学分。

那么分两种情况讨论：
1. $cha>r-a_i$（即就算这一科的学分拉满，也无法达到需要的分）

为了更优，我们肯定会要能获得的学分。

这时，$cha$ 需要去掉新加的 $r-a_i$ 分，$ans$ 需要加上新写的论文数量 $(r-a_i)\times b_i$ 篇。

该部分代码：
```cpp
cha=cha-(r-a[i]);//更新剩余学分
ans=ans+(r-a[i])*b[i];//更新总论文数
```

2. $cha\le r-a_i$（即仅还需这一科，就可以达到需要的分）

这时，只需要获得 $cha$ 分，所以 $ans$ 只需要加上新写的论文数量 $cha\times b_i$ 篇。

该部分代码：
```cpp
ans+=cha*a[i];//更新总论文数，cha=0，不必再统计，直接break
break;
```

为了方便排序，只需再加一个结构体就行了。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long//不开long long见祖宗
using namespace std;
struct node{
	ll a,b;
}a[100005];
ll n,r,avg,cha,ans;
bool cmp(node x,node y){
	return x.b<y.b;
}
int main(){
	cin>>n>>r>>avg;
	for(int i=1;i<=n;i++){
		cin>>a[i].a>>a[i].b;
		cha+=a[i].a;//统计和
	}
	cha=n*avg-cha;//还要多少学分
	if(cha<=0){//学分超了
		cout<<0;
		return 0;
	}
	sort(a+1,a+1+n,cmp);//将b从小到大排
	for(int i=1;i<=n;i++){
		if(cha>r-a[i].a){//这一科学分满了也还不够
			cha=cha-r+a[i].a;//更新剩余学分
			ans=ans+(r-a[i].a)*a[i].b;//更新总论文数
		}
		else{//这一科足矣
			ans+=cha*a[i].b;//更新总论文数，cha=0，不必再统计，直接break
			break;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：XL4453 (赞：0)

题目分析：

~~你写的论文数 int 是存不下的。~~

考虑贪心，想要尽量少写论文，那就先写每学分要写论文少的科目。

实现上按照每学分写论文数量排序，然后一科一科写，一直写到拿完学分。

------------

其实这题一开始我想到的是一个多重背包，但发现其实不需要。

因为每个物品的价值一定且为1，也就不存在一般背包中存在的剩余空间问题，所以转移时所需要的代价肯定是越少越好。

------------
代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long n,r,avg,now,avgn;
long long ans;
struct node{
	long long a,b;
}p[100005];
int cmd(node a,node b){
	return a.b<b.b;
}
int main(){
	scanf("%lld%lld%lld",&n,&r,&avg);
	avgn=avg*n;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&p[i].a,&p[i].b),avgn-=p[i].a;
	sort(p+1,p+n+1,cmd);
	now=1;
	while(avgn>0){
		if(avgn>r-p[now].a){
			ans+=p[now].b*(r-p[now].a);
			avgn-=r-p[now].a;
			now++;
		}
		else{
			ans+=p[now].b*avgn;
			break;
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

