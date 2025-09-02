# Door Frames

## 题目描述

Petya有一些长度为 n 的木条。他想要为两个一样的门做一个框架。每个框架都有两个竖直的长度为 a 的边（左边和右边）和一个长度为 b 的顶边。每个边都需要一个实心的（即不间断的）木条。

求出为两个门做框架所需要的最少的木条。Petya可以将一个木条切成几段，但是门的每一边都应该是完整的一块木板。

## 样例 #1

### 输入

```
8
1
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5
3
4
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6
4
2
```

### 输出

```
4
```

## 样例 #4

### 输入

```
20
5
6
```

### 输出

```
2
```

# 题解

## 作者：Chengjintian (赞：4)

# CF910B Door Frames题解

[题面](https://www.luogu.com.cn/problem/CF910B)


1、题意
------------
>给出三个值：$n,a,b$。现在有一些长度为 $n$ 的**原木条**。求至少要多少个这种长 $n$ 的原木条才可以制成 $4$ 个长度为 $a$ 和 $2$ 个长度为 $b$ 的**木条**。要求：长为 $n$ 的原木条可以被截断，但是不可以拼接。
>

 这题题面有点难理解，所以我将它简化了一下。注意：题目要求制作 $2$ 扇门框，所以目标长度是 $2(2a+b)$。
 
 
2、思路
------------
理解完题目，这道题就很好做了，我们考虑 **贪心** ，想要让长度为 $n$ 的原木条的数量最少，我们肯定要把原木条重复利用。

比如，现在有一根长为 $7$ 的原木条，制作长度为 $4$ 和 $1$ 的木条，我们把原木条截成 $3$ 段：$4,1,1,1$。这样最大化了原木条可产生的利益，理解了这个思路，这道题就成功一半了。

我使用 $pos1$ 和 $pos2$ 指向要制作的木条，然后去截断原木条。如果原木条不能再截成任何长度的木条，就直接丢掉，换下一个新的。

如下图（~~有点抽象~~）：

![图1](https://cdn.luogu.com.cn/upload/image_hosting/791g72jb.png)

这张图模拟了~~压榨原木条的过程~~，我们可以所以，如果原木条的剩下部分可以再截木条，就一直 while 循环直到达成目标。

**需要注意，我们的产出应该和需求相匹配，如果我们的任意木条生产达标了，那我们就没必要继续生产，浪费原木条了。**

我的代码因为将未产出的木条定死在数组 $bf$ 里了，所以不用担心有多产出的情况。如果你的思路和我不一样，没有用数组，那么一定要加一个特判，判断生产的某一木条数是否达标，如果达标，就不用继续生产，浪费原木条。

3、代码
------------

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a,b,sum=1,mt;
ll bf[7];
//解释：sum 表示最少用的原木条， mt 表示原木条还有多长
//bf[]表示待制作部分 
int main(){
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);//加快输入输出，注意，加了这句话就不能用printf 和 scanf了 
	cin>>n>>a>>b;
	mt=n;//拿起第1个原木条 
	for(int i=1;i<=4;i++)bf[i]=a;//将木条导入待制作中 
	for(int i=5;i<=6;i++)bf[i]=b;
	//这时bf[]内的样子就像上图一样 
	ll pos1=1,pos2=6;//指针指向待制作的第一个和最后一个 
	
	while(pos1<=pos2){
		if(mt-bf[pos1]<0 and mt-bf[pos2]<0){//如果原木条不能截成任何木条，sum++，并且换上新原木条 
			mt=n;
			sum++;
		}
		if(mt-bf[pos1]>=0){ //判断是否可以截出pos1指向的木条 
			mt-=bf[pos1];//截断 
			pos1++;//指向下一个 
		}
		if(mt-bf[pos2]>=0){//判断是否可以截出pos2指向的木条
			mt-=bf[pos2];//截断
			pos2--;//指向上一个 
		}
	}
	cout<<sum;
	return 0;
}
```
[AC  记录](https://www.luogu.com.cn/record/117663129)

---

## 作者：Zouzhuoxuan (赞：3)

# CF910B Door Frames 题解
## [Luogu 题目传送门](https://www.luogu.com.cn/problem/CF910B) / [Codeforces 题目传送门](https://codeforces.com/problemset/problem/910/B)
## [博客观感更好](https://www.luogu.com.cn/blog/800322/cf910b-door-frames-ti-xie)
---------------
## 一、题意简述
有无数根长度为 $n$ 的木棍，现在需要做 $2$ 个完全一样的门框，每个门框需要使用 $2$ 根长度为 $a$ 的木棍和 $1$ 根长度为 $b$ 的木棍。木棍可以分割但是不能拼接。求使用最少的木棍数。

## 二、算法分析
我们转化一下题意，就是让我们用最少的长度为 $n$ 的木棍凑出 $4$ 根长度为 $a$ 和 $2$ 根长度为 $b$ 的木棍。

我们不妨分别设长度为 $a,b$ 的木棍为 $A$ 型、 $B$ 型木棍，设供我们使用的木棍为 $N$ 型木棍，注意到**木棍可以分割但是不能拼接**，并且本题数据范围很小（$1\le a,b\le n\le 1000$），所以考虑使用 DFS 暴力搜索。定义 `void dfs(int as,int bs,int used,int len)`。其中 $as,bs$ 分别代表制作出来 $A$ 型、 $B$ 型木棍的数量，$used$ 代表使用的 $N$ 型木棍的数量，$len$ 代表上一根木棍还剩下的长度，当 $as=4$ 且 $bs=2$ 时维护使用 $N$ 型木棍的最小值即可。

## 三、完整代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 1e18
using namespace std;
int a,b,n,ans=INF;
void dfs(int as,int bs,int used,int len)
{
    if(as<0||bs<0) return; //如果制作出太多的木棍了，就返回
    else if(as==4&&bs==2) {ans=min(ans,used);return;} //如果木棍做好了就维护最小值ans
    else
    {
        if(len>=a) dfs(as+1,bs,used,len-a); //如果可以用剩下的木棍做就用
        else dfs(as+1,bs,used+1,n-a); //不然就舍弃那根木棍，重新使用一根新的
        if(len>=b) dfs(as,bs+1,used,len-b); 
        else dfs(as,bs+1,used+1,n-b); //此处同上
    }
}
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n>>a>>b;
    dfs(0,0,0,0); //开始DFS
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：haozinojc (赞：2)

这道题我的思路跟别人的有点不太一样，我用的是经典 DFS。

### 思路：

由题意可得：我们要准备 $4$ 个长为 $a$ 的木板（门两边的）和 $2$ 个长为 $b$ 的木板（门上面的）。

不过对于每种木板，我们不能用拼接起来的木条制成，题目都说了，要用**完整的**木条。当然，一个木条是有可能制成多个木板的（只要它够长）。

有很多大佬选择手打枚举每种情况，但我比较懒，所以要让电脑帮我枚举，说到这，大家都知道我要用 DFS 了。

确定方向后，剩下的就很简单了，设 $c$ 为还没制作好的门框两边部分数量，$k$ 为还没制作好的门框上部分数量，那么很显然，$c$ 的初始值为 $4$，$k$ 的初始值为 $2$。至于枚举部分，大家都会，我放下面了。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b,ans=1e12;
void dfs(int c,int k,int num,int l){
	if(c<0||k<0)return;
	if(c==0&&k==0){
		ans=min(ans,num);
		return;
	}
	if(l>=a)dfs(c-1,k,num,l-a);
	else dfs(c-1,k,num+1,n-a);
	if(l>=b)dfs(c,k-1,num,l-b);
	else dfs(c,k-1,num+1,n-b);
}
signed main(){
	cin>>n>>a>>b;
	dfs(4,2,0,0);
	cout<<ans;
	return 0;
} 
```


---

## 作者：YUYGFGG (赞：2)

暴力全排列做法

一共需要4a+2b长度的木板，将aaaabb全排列，一共有15种情况，所以可以将所有情况都尝试一遍，选择最佳答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[20][8],k;
void per(string s)  {  
    k = 0;
    sort(s.begin(),s.end());  
    do{ 
        k++;
        for(int i=0;i<s.size();i++) {
            c[k][i]=s[i];
    }     
    }while(next_permutation(s.begin(),s.end()));  
}  
int main(){
    int n,a,b,sum,ans,cnt ;
    string s="aaaabb";
    per(s);
    cin>>n>>a>>b;
    ans=10000;
    for(int i=1;i<=k;i++){
        sum=n;cnt=0;
        for(int j=0;j<=5;j++){
            if(c[i][j]=='a') sum-=a;
            if(c[i][j]=='b') sum-=b;
            if(sum<0){
                sum= n;
                if(c[i][j]=='a') sum-=a;
                if(c[i][j]=='b') sum-=b;
                cnt++;
            }
            if(j==5&&sum>=0) cnt++;
        }
        if(cnt<ans)
            ans=cnt;
    }
    cout<<ans<<endl;
    return 0;
}
```


---

## 作者：liukangyi (赞：1)

# 题目大意
给你一种长度为 $n$ 的木条，让你制造出两扇需 $2$ 条长度为  $a$ 的木棒与 $1$ 条长度为 $b$ 的木棒的门，而且木条**不能拼接**。问你至少需要几根长度为 $n$ 的木条才能完成这项造门的任务。


------------
# 分析
首先我们先来理解一下题目：让你制造出两扇那样的门，其实就相当于让你利用无限根长度为 $n$ 的木条构造出 $4$ 个长为 $a$ 和 $2$ 个宽为 $b$ 的木棒，木条不能拼接也就是告诉你如果一根木条剩余的部分不够再完成一个木棒，那么你也**不能通过另一根木条的帮助（拼接）来构造出这跟木棒**。既然已经确定需要切割成哪些木棒了，其实就很简单了，问题只是在于这些木棒的先后顺序可能会导致结果的不同，所以在我们没有办法确定它们的先后顺序时，我们不妨用回溯来枚举顺序，并通过计算所需木条数来更新最小值。



------------

### 计算所需木条数代码段
```cpp
int getNum(){
	int sum=0,Count=1;
	for(int i=1;i<=6;i++){
		sum+=path[i]; //path数组是回溯过程中的路径
		//如果目前长度之和大于木条n的长度，则将所需木条数加1，并把长度和设为路径上当前木棒的长度值 
		if(sum>n)
			Count++,sum=path[i];
	}
	return Count;
}
```
回溯的话大家套一下模板即可。

# 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,cntA,cntB,ans=INT_MAX; 
int path[10];
//定义变量。cntA代表a长度的个数，cntB代表b长度的个数，ans记录所需的最少木条数，

//回溯到终点时计算需要的木条数 
int getNum(){
	int sum=0,Count=1;
	for(int i=1;i<=6;i++){
		sum+=path[i];
		//如果目前长度之和大于木条n的长度，则将所需木条数加1，并把长度和设为路径上当前木棒的长度值 
		if(sum>n)
			Count++,sum=path[i];
	}
	return Count;
}

//回溯 
void dfs(int step){//step为当前回溯深入步数 
	if(step==7){
		ans=min(ans,getNum());
		return ;
	}//如果已经到了终点，则更新最小值
	 
	if(cntA<4){
		cntA++;
		path[step]=a; 
		dfs(step+1); //递归调用函数->进行下一步 
		cntA--;
	}//如果a长度的个数还没达到4根，那么尝试在此处走a这条路  
	
	if(cntB<2){
		cntB++;
		path[step]=b;
		dfs(step+1);
		cntB--;
	}//如果b长度的个数还没达到2根，那么尝试在此处走b这条路  
}
int main(){
	cin>>n>>a>>b; 
	dfs(1); //从最开始，即1处开始进行回溯 
	cout<<ans;
	return 0;
}

```



---

## 作者：流绪 (赞：1)

DFS！

我们一共要切出 4 块竖边,2 块横边,对于组成门的每一块木板他有两种来源：⑴由一块新的木板切割而来 ⑵由一块新的木板切割而来。再一看题目数据很小，那直接搜索啊！每次传入的数据分别是:x 还没凑出的竖边数量,y 还没凑出的横边数量,sum 现在共用了几块木板,len 当前木板还剩多长。

然后我们每次看看剩下的长度够不够切，不够就拿新的木板来切。同时注意把不合法的情况 return 掉，比如 x,y<0。然后就是 x=0,y=0，更新答案就好啦。这里不需要回溯,因为我们没有改变搜索时原来状态的量,细节都注释在代码里了。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int n,a,b;
int ans = inf;
void dfs(int x,int y,int sum,int len)
{
//	cout << x << " " <<y <<" " << sum << " " <<len<<endl; 
	if(x<0||y<0)
		return;
	if(!x&&!y)
	{ 
		ans = min(ans,sum);//更新答案
		return;
	}
	if(len >= a)
		dfs(x-1,y,sum,len-a);//剩的木板可以切出a
	if(len >= b)
		dfs(x,y-1,sum,len-b);剩的木板可以切出b
	if(len < a )
		dfs(x-1,y,sum+1,n-a);剩的木板不够切a
	if(len < b)
		dfs(x,y-1,sum+1,n-b);剩的木板不够切b
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> a >> b;
	dfs(4,2,0,0); 
	cout << ans ;
	return 0; 
}   
```


---

## 作者：liulianLL (赞：0)

# CF910B Door Frames题解

[题目传送门](https://www.luogu.com.cn/problem/CF910B)

## 一、题意

给定 $n,a,b$ ，要求将若干条长度为 $n$ 的木棍切割成 $4$ 条长度为 $a$ 的木棍与 $2$ 条长度为 $b$ 的木棍，求最少要使用多少根木棍。

## 二、分析

注意到题目中数据范围较小，考虑使用深搜。

定义函数 ```dfs(int x,int y,int l,int p)``` ，其中 $x,y$ 分别表示还需制造长为 $a,b$ 的木棍的数量，$l$ 表示当前所切木棍的剩余长度，$p$ 表示当前所用木棍数量。

对于每一次搜索，有以下几种操作：

- 切换一根新的木棍。
- 从当前使用的木棍中切下一根长为 $a$ 的木棍。
- 从当前使用的木棍中切下一根长为 $b$ 的木棍。

当 $x,y$ 均为 $0$ 时，更新答案。

## 三、优化

注意到若一根木棍的剩余长度比 $a$ 或 $b$ 大，则执行切换木棍的操作一定不是最优选择。因此，我们无需单独执行切换木棍的操作，而是在切下木棍时进行判断。

## 四、代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,n1,ans=7;
void dfs(int x,int y,int l,int p){
	if(x+y==0){
		if(p<ans) ans=p;
		return;
	}
	if(x>0){
		if(l>=a) dfs(x-1,y,l-a,p);
		else dfs(x-1,y,n-a,p+1);
	}
	if(y>0){
		if(l>=b) dfs(x,y-1,l-b,p);
		else dfs(x,y-1,n-b,p+1);
	}
}
int main()
{
	scanf("%d%d%d",&n,&a,&b);
	dfs(4,2,n,1);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：yghjsk (赞：0)

# 题意：
这题给我们了一些长度为 $n$ 的木条，要我们为两扇门用这些木条做两边长度为 $a$ 与一条 $b$ 的门框，问我们至少要多少条完整的木板。
# 思路：
这题有的大佬用回溯，有的用数学方法，还有的用暴力枚举，有些本蒟蒻不理解，就用刚学的 DFS 做了，大佬勿喷！

要做两个门框，也就是 $4$ 个 $a$，$2$ 个 $b$，题目说了要用完整的木条，也就是数量是整数的。

那我们枚举竖边，横边，用几块，剩多长，然后每次递归看看剩下的长度够不够切，不够就拿新的木板来切，数量累加，不合法的情况就 return，返回上个递归，然后不断更新最小答案就好啦。
# 你们最爱的完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a,b,zx=1e12;
void dfs(int s1,int s2,int s3,int s4){
	if(s1<0||s2<0)return;
	else if(s1==0&&s2==0){
		zx=min(zx,s3);
		return;
	}
	if(s4>=a)dfs(s1-1,s2,s3,s4-a);
	if(s4<a)dfs(s1-1,s2,s3+1,n-a);
	if(s4>=b)dfs(s1,s2-1,s3,s4-b);
	if(s4<b)dfs(s1,s2-1,s3+1,n-b);
}
signed main(){
	cin>>n>>a>>b;
	dfs(4,2,0,0);
	cout<<zx;
	return 0;
} 
```
官方求过，求求啦！




---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，可知切割方案为字符串 aaaabb 的全排列，把所有方案枚举一遍，便可知所需的最小木条数。  
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,ans=1e9;
string s="aaaabb";
int get(string x){
	int s=n,sum=1,m;
	for(int i=0;i<6;i++){
		if(x[i]=='a'){
			m=a;
		}
		if(x[i]=='b'){
			m=b;
		}
		if(s<m){
			s=n-m;
			sum++;
		}
		else{
			s-=m;
		}
	}
	return sum;
}
int main(){
	cin>>n>>a>>b;
	do{
		ans=min(ans,get(s));
	}while(next_permutation(s.begin(),s.end()));
	cout<<ans;
	return 0;
}
```


---

## 作者：Level_Down (赞：0)

同样是暴力全排列做法，不过自认为比楼上的更加简洁易懂。

在全排列的时候，可以不必将使用顺序用字符串存储，而可以用数组代替，其中数组的值为 $1$ 时，则代表使用 $a$，值为 $0$，使用 $b$，同时，也可以以此作为判断时寻找 $a$、$b$ 长度的指针，代码参考如下：


```cpp
int a[2],x[6] = {0,0,1,1,1,1}
//其中a[0]为题目输入中的a，a[1]为b
//a[x[i]]即为当前循环到的需用长度
```

这样就可以直接使用 STL 中的 `next_permutation`，而不必自己再重新写一个函数代替了。

还要再提一下的是判断全排列结束的方法，全排列结束时 $x$ 数组必为 `111100`，所以若 $x$ 数组最后两位都是 $0$时，全排列结束；或是通过计算得出共有 $15$ 种全排列，直接通过 $1$ 到 $15$ 的循环结束也行。

代码：

```
#include <bits/stdc++.h>
using namespace std;
int n,a[2],x[6] = {0,0,1,1,1,1},ans = 7,T = 15;
int main()
{
	cin >> n >> a[1] >> a[0];
	while(!(x[4] == 0 && x[5] == 0))
    //这里还能写while(T--) 
	{
		int sum = 1,cnt = 0;
		for (int i = 0; i < 6; i++)
			{
				if (cnt + a[x[i]] > n) cnt = a[x[i]],sum++;
				else cnt += a[x[i]];
			}
		ans = min(sum,ans);	
		next_permutation(x,x + 6);
	}	
	cout << ans;
	return 0;
}
```

若有问题可在评论区中提出或是私信。

---

