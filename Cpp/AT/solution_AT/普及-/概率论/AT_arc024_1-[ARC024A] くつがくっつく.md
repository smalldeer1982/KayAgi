# [ARC024A] くつがくっつく

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc024/tasks/arc024_1

ARCマートは土曜日だけに営業する靴屋さんです。扱う靴は$ 1 $種類だけで、サイズ以外の見分けはつきません。 残念なことに、 $ 1 $ 週間ぶりに店を開けると空き巣に入られてしまったらしく、靴がめちゃくちゃに散乱していました。

残っている靴を全部かき集めると、左足の靴が $ L $ 足、右足の靴が $ R $ 足みつかりました。 ただ、靴を売るには同じサイズを両足分そろえてペアにしなければなりません。 靴の種類はすべて同じなので、ペアを作るときはサイズだけを気にすれば良さそうです。

もう開店まで時間がないので、店長のために、最大で何組のペアを作ることができるか求めてください。

## 说明/提示

### Sample Explanation 1

サイズ $ 22 $ のペアが $ 1 $ つだけ作れます。

### Sample Explanation 2

サイズ $ 10 $ 、サイズ $ 11 $ のペアがそれぞれ $ 1 $ つずつ作れます。

## 样例 #1

### 输入

```
3 3
20 21 22
30 22 15```

### 输出

```
1```

## 样例 #2

### 输入

```
3 4
10 11 10
12 10 11 25```

### 输出

```
2```

## 样例 #3

### 输入

```
5 5
10 10 10 10 10
10 10 10 10 10```

### 输出

```
5```

## 样例 #4

### 输入

```
5 5
10 11 12 13 14
30 31 32 33 34```

### 输出

```
0```

# 题解

## 作者：JJA_ (赞：6)

### 思路

只需要使用`map`记录左边每个号码出现的次数，`map[left]++;`之后输入右边时再判断`map[right]`有没有被记录过，若有，则`map[right]--;`，`sum++;`若没有，则跳过。由于`map`是一对一哈希值，所以复杂度能过。

---
### 代码完成

实在没什么好讲的，`map`使用能看[这里](https://blog.csdn.net/sevenjoin/article/details/81943864)，个人认为讲的很清楚。主要思路就是暴力。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum=0;
map<int,int>type;
signed main(){
	int L,R;
	cin>>L>>R;
	int left,right;
	while(L--){
		cin>>left;
		type[left]++;
	}
	while(R--){
		cin>>right;
		if(type[right]!=0){
			sum++;
			type[right]--;
		}
	}
	c‬out<<sum<<endl;
}
```
望采纳，谢谢。

---

## 作者：ByGones (赞：6)

这道题的数据范围非常小 $O(n^2)$ 也能过，我看许多大佬都是双重循环暴力枚举，还没有人用优先队列做，我就用优先队列 $(priority\_queue)$ 做一下试试吧。

优先队列和普通的队列有很多相似之处，但它能把加进去的数从大到小排序，而且时间复杂度是 $O(logn)$ ~~好像是的吧~~，因此十分好用。

提醒一下，和普通队列不同，优先队列的队首是 $top$ 而不是 $front$。

做这道题我不知怎么的想起了双飞燕，可能有点相似吧，下面贴出代码。

**代码如下**

```cpp
#include <bits/stdc++.h>
using namespace std; 
priority_queue<int>l,r;//定义两个优先队列l和r
int L,R,s;
int main()
{
	cin>>L>>R;
	while(L--)
	{
		int t;
		cin>>t;
		l.push(t);//把左鞋码数加进优先队列中
	}
	while(R--)
	{
		int t;
		cin>>t;
		r.push(t);//把右鞋码数加进优先队列中
	}
	while(!l.empty()&&!r.empty())//如果左鞋和右鞋都还有
	{
		if(l.top()==r.top())//如果能配成一对
		{
			l.pop();
			r.pop();
			s++;//数量++
		}
		else if(l.top()<r.top())
			r.pop();
		else
			l.pop();
	}
	cout<<s<<endl;
	return 0;
}
```
**提醒：行末一定要有换行，不然会被判为答案错误** **~~，所以我们可以多用puts()~~,在最后输出换行是个好习惯**

此代码可以AC，大家看着代码自己理解一下，也可以去找几道优先队列的题目再练练

---

## 作者：Cripple_Abyss (赞：5)

## [题目传送门](https://www.luogu.com.cn/problem/AT882)

## STEP 1 大致题意：
- 给定两个序列，求这两个序列中相同元素的个数。

## STEP 2 题目解法：
- 用两个桶分别记录这两个序列中每个元素的个数。

- 最终答案就是 $\sum_{i=10}^{40} min (l[i],r[i])$ 。

## STEP 3 Code （超短）:
```cpp
#include <cstdio>
int n,m,l[55],r[55],ans;
int mn(int x,int y) {return x<=y?x:y;}
int main() {
	scanf("%d%d",&n,&m);
	for (int i=1,x; i<=n; ++i) scanf("%d",&x),l[x]++;
	for (int i=1,x; i<=m; ++i) scanf("%d",&x),r[x]++;
	for (int i=10; i<=40; ++i) ans+=mn(l[i],r[i]);
	printf("%d\n",ans);
	return 0;
}
```

都看到这里了，点个赞再走呗 QwQ

---

## 作者：Chtholly_L (赞：2)

#  AT882 【くつがくっつく】题解

~~大家好，我又是那个奆蒟蒻，我又双叒叕来写题解了~~

~~这是一道蓝题，看起来好难啊，像我这种奆蒟蒻早就敬而远之了，但是，某种神秘的力量吸引我来 $AC$ 这道题~~

废话不多说了，开始讲解。

我把题干再进一步翻译，如下：

**输入 $L$ ， $R$ ，接下来输入两行，第一行 $L$ 个数据，第二行 $R$ 个数据**

**问这两组数，有多少组数是相等的，而且已经和别的数组成相等的数就不能和别的数组成了。**

乍一看，还挺简单，难点就在怎样判断这个数是不是已经和别的数组成过了。

我有一个办法，就是用两组数组来记录这个数是不是已经被用过了， $0$ 代表未用过， $1$ 代表已用过,用完了之后就把 $0$ 变成 $1$ 。

更具体的解说在代码里

上代码

## $Ac$ $Code$

```cpp
#include<iostream>
using namespace std;
long long a[101],b[101];  //左脚的鞋和右脚的鞋
int ab[101]={},bb[101]={};  //判断是否被用过的两个数组
int main()
{
    long long l,r,ans=0;
    cin>>l>>r;
    for(int i=1;i<=l;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=r;i++)
    {
	cin>>b[i];
    }
    for(int i=1;i<=l;i++)  //枚举左脚的鞋
    {
	for(int j=1;j<=r;j++)  //枚举右脚的鞋
	{
	    if(a[i]==b[j] and ab[i]==0 and bb[j]==0)  //同时满足相等且没被用过
	    {
		ans++;  //计数器加一
		ab[i]=1;  //标记用过
		bb[j]=1;  //标记用过
	    }
	}
    }
    cout<<ans<<endl;  //输出个数
    return 0;  //结束程序
}

```
~~本奆蒟蒻第3次写题解了，望管理员帅哥/美女通过~~~

~~话说，这是我的第一道蓝题欸~~

[评测记录](https://www.luogu.com.cn/record/46282968)

[博客食用更佳](https://www.luogu.com.cn/blog/maxsuper/)

博客里还有其他很好的题的题解，欢迎捧场

---

## 作者：MarchKid_Joe (赞：2)

[AT882 くつがくっつく](https://www.luogu.com.cn/problem/AT882)

# 1. 题意
给出$n$个鞋码，在$m$中寻找与之对应的鞋码

# 2. 做法
**桶排**：思想十分简单，**下标**排序。所以这道题做法就是用桶排这一思想，分别存储左鞋的鞋码和右鞋的鞋码，然后再枚举，从10循环到40，寻找同样鞋码的左鞋和右鞋的**最小值**（要配对肯定要找最少的... ...）并累加。

# 3. $CODE$
```cpp
#include<cstdio>
#define min(a,b) a<b?a:b//手打min
#define rep(i,s,e) for(i=s;i<=e;i++)//终究还是活成自己讨厌的样子
using namespace std;
int n,m,l[50],r[50],ans,i,x;
int main()
{
	scanf("%d%d",&n,&m);
	rep(i,1,n) scanf("%d",&x),++l[x];
	rep(i,1,m) scanf("%d",&x),++r[x];
	rep(i,10,40) ans+=min(l[i],r[i]);
	printf("%d\n",ans);
	return 0;
}
```
## Warning："\n"

---

## 作者：USACO_CHENWJ (赞：2)

# 思路：
首先想到的就是~~暴力~~  
~~暴力大法吼啊~~   
1.输入（分开两个数组~~为了好暴力~~）
```cpp
for(i=1;i<=n;i++)
   cin>>l[i];
for(i=1;i<=m;i++)
   cin>>r[i];
```
2.一个i，一个j，暴力搜   
### 注意：   
### 1.已经卖出的鞋子不能再卖，so要标记，开个数组  
### 2.鞋子卖出要码数相同
```cpp
for(i=1;i<=n;i++)
{
   for(j=1;j<=m;j++)
   {              
		//爆搜
		if(l[i]==r[j]&&l1[i]==false&&r1[j]==false)
      {
      	sum++;
       l1[i]=true;//标记一下
       r1[j]=true;
      }
    }
}    
```
3.输出（岛国题要回车）
```cpp
cout<<sum<<endl;
```
# 总代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x,i,j,l[1000],sum,r[1000];
bool l1[1000],r1[1000];
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>l[i];
    }
    for(i=1;i<=m;i++)
        cin>>r[i];
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(l[i]==r[j]&&l1[i]==false&&r1[j]==false)
            {
                sum++;
                l1[i]=true;
                r1[j]=true;
            }
        }
    }    
    cout<<sum<<endl;
    return 0;
}
```
望各位大佬指出错误，并私信我，谢谢



---

## 作者：zcl1024 (赞：2)

这道题数据比较小（10..40），桶排即可
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[100],b[100];//a是左鞋的码数，b是右鞋的码数
int main(){
    int l,r;
    int i;
    int x;
    cin>>l>>r;
    for (i=1;i<=l;i++){
        cin>>x;a[x]++;//桶排
    }
    for (i=1;i<=r;i++){
        cin>>x;b[x]++;//桶排
    }
    int ans=0;
    for (i=10;i<=40;i++) ans+=min(a[i],b[i]);//选同码的左鞋右鞋只数小的那个
    cout<<ans<<endl;
    return 0;
}

```

---

## 作者：TRZ_2007 (赞：2)

## 看着这道题，心中不由地想起来了找筷子……
### 好像就是吧！
这题我是用桶来做的，首先定义两个数组——$l$和$r$。来表示鞋子的尺码，又定义了两个桶——$listl$和$listr$来表示鞋子。也就是说，$listl[i]$是表示$l[i]$这个鞋子用过没有，$listr[i]$也是这样表示的。  
那么，就上代码了。
```
#include <stdio.h>//stdio头文件比较好用
int l[101],r[101];//表示鞋子的尺码
int listl[101],listr[101];//表示鞋子用没用过
int L,R;//有L双左鞋，R双右鞋
bool find(int n,int i)//寻找左鞋是否与右鞋相配
{
	int j;
	if(listl[i]==1) return false;//用过了就返回false
	for(j=1;j<=R;j++)//开始查找
		if(r[j]==n) //如果找到了
		{
			if(listr[j]==1)//但是却用过了
				continue;//还是得继续找
			listr[j]=1;//否则就标记用过了
			return true;//返回true表示找到了
		}
	return false;//没找到返回false
}
int main()
{
	int ans=0,i,j;//ans最初必须是0
	scanf("%d %d",&L,&R);
	for(i=1;i<=L;i++)//读入左鞋
		scanf("%d",&l[i]);
	for(i=1;i<=R;i++)//读入右鞋
		scanf("%d",&r[i]);
	for(i=1;i<=L;i++)//开始查找
		if(find(l[i],i)) //如果找到了
		{
			ans++;//个数自加
			listl[i]=1;//这双左鞋也用过了
		}
	printf("%d\n",ans);//输出个数
}
```

---

## 作者：RioBlu (赞：2)

进行桶排统计
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c[50],d[50],ans,n;
int main()
{
	cin>>a>>n;
	for(int s=0;s<a;s++)
	{
		cin>>b;
		c[b]++;//左鞋子b码+1
	}
	for(int s=0;s<n;s++)
	{
		cin>>b;
		d[b]++;//右鞋子b码+1
	}
	for(int s=10;s<=40;s++)
	ans+=min(d[s],c[s]);//min(d[s],c[s])代表能凑够多少双)
	cout<<ans<<endl;
}
```

---

## 作者：EuphoricStar (赞：1)

这道题我的思路是：

建立两个数组，$lcnt$ 和 $rcnt$，$lcnt_i$ 表示码数为 $i$ 的左鞋共有几只，对应地，$rcnt_i$ 表示码数为 $i$ 的右鞋共有几只。

读入每一个 $l_i$ 和 $r_i$，$lcnt_{l_i}$ 或 $rcnt_{r_i}$ 就 $+1$。

最后遍历这两个数组，对于 $lcnt_i$ 和 $rcnt_i$ 取最小值（表示码数为 $i$ 的鞋最多可以配多少对）并累加至 $ans$ 中，最后输出 $ans$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, l, r, lcnt[45], rcnt[45], ans;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        int l;
        scanf("%d", &l);
        ++lcnt[l];
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", &r);
        ++rcnt[r];
    }
    for (int i = 10; i <= 40; ++i) {
        ans += min(lcnt[i], rcnt[i]);
    }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：翰森锐 (赞：1)

## 看了上面的dalao，我才发现我的做法快多了。。。

这题很简单，不知道为什么岛国人民....算了不说了

我们只要模拟题目，边输边记录，最后输出。

不用再多一个循环特意查找，只要边读边记录，

在第二次输入时查找数组里的这个位置是否为真（非零，且等零时不会继续造成负数而error），是的话表示已配对，最后输出配对数

code：
```cpp
#include<bits/stdc++.h>//van♂能头
using namespace std;
long long a[10000001],l,r,k,ans;
int main()
{
	cin>>l>>r;//左右
	for(int i=0;i<l;i++)
	{
		cin>>k;
		a[k]++;//尺码++
	}
	for(int i=0;i<r;i++)
	{
		cin>>k;
		if(a[k])//如果这个尺码出现过
		{
			a[k]--;//因为出现并配对了，所以减一双
			ans++;//计数器++
		}
	}
	cout<<ans<<endl;//大坑，因为岛国人民喜欢换行
    return 0;
}
```
不瞒你说，时间复杂度是O(n)，FAST！！

管理员你太美！！！

---

## 作者：Ouyyx2002 (赞：1)

```cpp
uses math;
var
   L,R,i,t:integer;
   A,B:array[10..40] of integer;
begin
   read(L, R);
 
   for i:=10 to 40 do
      begin
        A[i]:= 0;
        B[i]:= 0;
      end;
   for i:=1 to L do
      begin
        read(t);
        inc(A[t]);
      end;
   for i:=1 to R do
      begin
        read(t);
        inc(B[t]);
      end;
   t:=0;
   for i:=10 to 40 do
      t:=t+min(A[i],B[i]);
   writeln(t);
end.
```

先贴代码再讲题。

此题意思是鞋子配对，能配出几双鞋子。

没有分类讨论直接做。

用A/B数组分别存储左右脚鞋子各码数的只数，然后依次查找，对于尺码i，能配成的双数是A[i],B[i]的最小值。

~~有点类似于……桶排？~~

~~说错了当我没说。~~

~~做题的时候忘记pas没有min函数了，然后ce了好久。~~

---

## 作者：想不好名字 (赞：1)

这是本蒟蒻第一篇题解，望各位神犇给予指导
说实话，看到蓝题，本蒟蒻还是很慌的  
—————————————————————//手动分隔符


好了，分析题意，这道题主要考验桶排（自己的理解），将左脚的和右脚的码数分别装到对应的桶里，然后再看是否两个对应的桶中同时含有元素；
话不多说，上代码
——————————————————————————

```c
#include<iostream>
#include<windows.h>  //不怕就复制
using namespace std;
int m,n;
int ans=0;
int r[10001],l[10001];
int main()
{
	int x,y;
	cin>>m>>n;
	for(int i=1;i<=m;++i) 
	{
		cin>>x;
		r[x]++;					//桶排特点，将对应的元素装到对应的桶
	}
	for(int j=1;j<=n;++j) 
	{
		cin>>y;
		l[y]++;				//同上
	}
	for(int i=10;i<=40;++i)
	{
		ans+=r[i]<l[i]?r[i]:l[i]; //比较有逼格的三目运算符，得到最多的鞋数
	}
	cout<<ans<<endl;
	return 0;
} 
```
## 管理员哥哥求过审

---

## 作者：梦里调音 (赞：1)

暴力出奇迹！

样例四真的别理！

我的思路是以左边鞋为基础找右边鞋配对。

算法：暴力

左边的鞋找到对应的鞋后就轮到下一只左边的鞋，并标记右边的鞋，其他左边的鞋就无法占有它了！

两个for循环，找到即标记，并进入下一个左鞋的for

代码里也有注释：

```
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
int l,r,ans=0;
int a[1001],b[1001],c[1001];
int main(){
	int i,j,k;
	scanf("%d%d",&l,&r);//输入
	for(i=1;i<=l;i++)cin>>a[i];//输入
	for(i=1;i<=r;i++)cin>>b[i];//输入
	sort(a+1,a+l+1);
	sort(b+1,b+r+1);//先快排（很显然快排后匹配更快）
	for(i=1;i<=l;i++)//左和右配对
	for(j=1;j<=r;j++)//枚举右鞋
		if(a[i]==b[j]&&c[j]==0){//符合码数且未使用——匹配成功！
			c[j]++;//标记——已使用
			ans++;//答案
			break;//左脚匹配完毕，白白
		}
	printf("%d\n",ans);//输出
	return 0;
}
```


---

## 作者：Nt_Tsumiki (赞：0)

## 题意
有 $L$ 双任意鞋号的左鞋和 $R$ 双任意鞋号的右鞋，求最多能组成几双鞋号相同的鞋
## 做法
设两个桶，
一个放左鞋号码，一个放右鞋号码，
求相同鞋号最大搭配双数：$\min(l_i,r_i)$，
加入计数器中最后输出

## 代码
```cpp
#include<iostream>
using namespace std;
int l[110],r[110],L,R,ans;
int main(){
	cin>>L>>R;
	for(int i=1;i<=L;i++){
		int t;
		cin>>t;
		l[t]++;//放入桶中
	}
	for(int i=1;i<=R;i++){
		int t;
		cin>>t;
		r[t]++;//放入桶中
	}
	for(int i=10;i<=40;i++){
		ans+=min(l[i],r[i]);//将最大双数加入计数器
	}
	cout<<ans<<endl;
   return 0;//不要忘了
}
```

---

## 作者：stry (赞：0)

~~这道题我怀疑是道极水的水题，根本配不上它蓝题的称号~~

大家好，这是我上初一的第一篇题解，希望dalao们多多包容，多多理解。

~~管理员求过~~

来分析一下这道题，题目意思是给你2n只鞋的鞋码，问能搭配出几双鞋。

看到这里，我不禁想起了

### 暴力枚举

数据也允许：100*100

#### 话不多说上程序：

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<cmath>
#include<cstdio>
using namespace std;
int a,b,h;
int aa[110],bb[110];//定义数组
int main()
{   
    cin>>a>>b;
    for(int i=0;i<a;i++)cin>>aa[i];	//输入左鞋的鞋码
    for(int i=0;i<b;i++)cin>>bb[i];	//输入右鞋的鞋码
    for(int i=0;i<a;i++)
    {
    	for(int j=0;j<b;j++)
    	{
    		if(aa[i]==bb[j]){h++;aa[i]=0;bb[j]=0;break;}
            //判断两双鞋的鞋码是否相等，相等就有一对鞋
            //重点：要清零，不清零会有另一双同样鞋码的鞋和它再次相加            
    	}
    }
    cout<<h<<"\n";//输出
    //重点2：岛国题换行。
    return 0;//完美撒花
}

谢谢观看

```


---

## 作者：A_Plus_Gu (赞：0)

又是恶意骗分...

此题很简单，根据题意~~膜你~~**模拟**即可~

我们一起来看代码吧...（~~挤不出话了~~）

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[10001],b,ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b;
		for(int j=1;j<=n;j++){
			if(b==a[j]){
				ans++;
           			//下面两句很重要，不可以省略
				a[j]=-1;//由于一双左鞋能且只能与一双右鞋对应，所以要把这个标记为已配对
				break;//由于一双左鞋能且只能与一双右鞋对应，所以找到这双右鞋所对应的左鞋后就不用再找了（能配对了还找个鬼qaq）
			}
		} 
	}
	cout<<ans<<endl;
}
```


---

## 作者：Ryo_Yamada (赞：0)

今天我[末影](https://www.luogu.org/blog/juruo12345/)又来水题解啦！

文章开头请求各位管理大大，这题显然是恶意评分，一个桶排而且数据极小的情况下能是蓝题？希望能改一下。

因为数据小，直接开数组存就好了。

代码君：
```cpp
#include <iostream>
#define LL long long
using namespace std;
LL l,r,c[50],d[50],ans;
int main(){
    cin >> l >> r;//左右鞋的个数
    for(int i=0; i<l; i++){
        int x;
        cin >> x;
  		c[x]++;
    }//读入左鞋
    for(int i=0; i<r; i++){
        int x;
        cin >> x;
        d[x]++;
    }//读入右鞋
    for(int i=10; i<41; i++){
    	ans += min(d[s],c[s]);//如果能配对，就有min(d[s],c[s])双，ans加上
    }//题目数据水，从10扫到40
    cout << ans << endl;//输出
    return 0;//完美结束
}反抄袭
```


---

## 作者：TCZN (赞：0)

这题...先上代码再说
```pascal
var
  l,r,s,i,n:longint;
  a,b:array[1..123] of longint;//大一点啦
begin
 read(l,r);
  for i:=1 to l do //输入←脚鞋子的码数，并将它暴♂力扔进桶里
   begin
    read(n);
    inc(a[n]);
   end;
    for i:=1 to r do //输入→脚鞋子的码数，并将它暴♂力扔进桶里
     begin
      read(n);
      inc(b[n]);
     end;
      for i:=10 to 40 do //因为鞋子的码数（数据范围）只有40码（最大到40），所以直接10 to 40就行了
       if a[i]>b[i] then s:=s+b[i]
        else s:=s+a[i]; //刚开始蒟蒻是if (a[i]>0) and (b[i]>0) then inc(s),这条语句碰到重复数据就会锅，如样例#3，就会输出1，所以要取小的一个（如果←鞋40码5只，而→鞋40码只有4只，就只能卖出4双，所以要取小的）
       writeln(s);
end.//完美结束
```
这题类似于桶排~~标签里不就有吗...~~

具体的不多说了，主要看代码注释

~~还是比较水的~~

---

## 作者：Rocket_raccoon_ (赞：0)

很明显的两个数组中的数字匹配问题    
因为数据相当小，直接暴力匹配即可    
注意匹配到之后要删掉（因为鞋子码数大于零，所以可以改成-1）

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a[1100],b[1100],ans;

int main(){
	int n,m,i,j;
	
	cin>>n>>m;
	
	for (i=1; i<=n; i++){
		cin>>a[i];
	}
	for (i=1; i<=m; i++){
		cin>>b[i];
	}//读入两个数组
	for (i=1; i<=n; i++){
		for (j=1; j<=m; j++){
			if (a[i]==b[j]){
				ans++;
				b[j]=-1;//匹配到就删掉并且答案加一
				break;//记得一定要退出
			}
		}
	}
	
	cout<<ans<<endl; //岛国题记得换行
	
	return 0;
}
```


---

