# [ABC050B] Contest with Drinks Easy

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc050/tasks/abc050_b

joisinoお姉ちゃんは、あるプログラミングコンテストの決勝を控えています。 このコンテストでは、$ N $ 問の問題が用意されており、それらには $ 1～N $ の番号がついています。 joisinoお姉ちゃんは、問題 $ i(1≦i≦N) $ を解くのにかかる時間が $ T_i $ 秒であることを知っています。

また、このコンテストでは、$ M $ 種類のドリンクが提供されており、$ 1～M $ の番号がついています。 そして、ドリンク $ i(1≦i≦M) $ を飲むと、脳が刺激され、問題 $ P_i $ を解くのにかかる時間が $ X_i $ 秒になります。 他の問題を解くのにかかる時間に変化はありません。

コンテスタントは、コンテスト開始前にいずれかのドリンクを $ 1 $ 本だけ飲むことができます。 joisinoお姉ちゃんは、それぞれのドリンクについて、それを飲んだ際に、全ての問題を解くのに何秒必要なのかを知りたくなりました。 全ての問題を解くのに必要な時間とは、それぞれの問題を解くのにかかる時間の合計です。 あなたの仕事は、joisinoお姉ちゃんの代わりにこれを求めるプログラムを作成することです。

## 说明/提示

### 制約

- 入力は全て整数である
- $ 1≦N≦100 $
- $ 1≦T_i≦10^5 $
- $ 1≦M≦100 $
- $ 1≦P_i≦N $
- $ 1≦X_i≦10^5 $

### Sample Explanation 1

一つ目のドリンクを飲んだ場合、それぞれの問題を解くのに要する時間は、$ 1 $ 秒、$ 1 $ 秒、$ 4 $ 秒になります。 なので、それらを合計した $ 6 $ 秒が答えになり、$ 6 $ を出力します。 二つ目のドリンクを飲んだ場合、それぞれの問題を解くのに要する時間は、$ 2 $ 秒、$ 3 $ 秒、$ 4 $ 秒になります。 なので、それらを合計した $ 9 $ 秒が答えになり、$ 9 $ を出力します。

## 样例 #1

### 输入

```
3
2 1 4
2
1 1
2 3```

### 输出

```
6
9```

## 样例 #2

### 输入

```
5
7 2 3 8 5
3
4 2
1 7
4 13```

### 输出

```
19
25
30```

# 题解

## 作者：智子·起源 (赞：13)

### “可笑名义上的监管，影身在迷雾之间，靠题解来获得存在感~~”红蝶带着阵阵迷幻又来写题解啦！


这道题，我发现前面几篇都好麻烦啊，我来一篇目前最简单的。
如果有新手实在不知道的，可以看一下下面的解释。
#### ~~红蝶小姐是关爱新手的^_^~~
代码献上：
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
int n,a[100+5],x,y,h;//定义
int main()
{
  scanf("%d",&n);//读入n
  for(int i=1;i<=n;i++){scanf("%d",&a[i]);h+=a[i];}//这里是读入a数组，然后记录下它们的和。
  scanf("%d",&n);//由于后面不需要n，所以这里我重新把n作为另一个变量（这样不好，大家不要学！）
  for(int i=0;i<n;i++)//这里的枚举范围也可以是1到n。
  {
    scanf("%d%d",&x,&y);//读入饮料的功效。
    printf("%d\n",h-a[x]+y);//直接求出喝当前饮料所需的时间，并输出。
  }
  return 0;
}
```
接下来是** _~~像红蝶一样美丽的~~_ **代码：（无注解）
```cpp
#include<iostream>
#include<cstdio>

using namespace std;
int n,a[100+5],x,y,h;
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++){scanf("%d",&a[i]);h+=a[i];}
  scanf("%d",&n);
  for(int i=0;i<n;i++)
  {
    scanf("%d%d",&x,&y);
    printf("%d\n",h-a[x]+y);
  }
  return 0;
}
```


---

## 作者：opened (赞：3)

这道题的解法有很多，可以用线段树、树状数组、分块、平衡树等毒瘤数据结构解出，而蒟蒻我只会模拟。

Talk is cheap, show me the code.
------------

	#include<iostream>
    #include<cstdio>
    using namespace std;
    int n,m,sum1,sum2,a[110];//维护和
    int main(){
        scanf("%d",&n);
        sum1=0;
        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            sum1+=a[i];
        }
        scanf("%d",&m);
        sum2=sum1;//轮番维护
        while(m--){
            int p,x;
            scanf("%d%d",&p,&x);
            if(x>=a[p-1]) sum1+=x-a[p-1];//按题模拟
            else sum1-=a[p-1]-x;
            printf("%d\n",sum1);
            sum1=sum2;
        }
        return 0;
    }

---

## 作者：雪风舞者 (赞：3)

这个题的数据说实话瞎暴力都可以。。。

然而~~懒得写~~锻炼自己的思维能力，于是记录$t_i$和其总和$sum$，每个饮料计算时，因为一个饮料只会影响一个题的时间，只需把对应的差值$t_p-x$计算上就好了。
```cpp
#include<cstdio>
using namespace std;
int n,m,a[105],sum=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	scanf("%d",&m);
	while(m--){
		int p,x;
		scanf("%d%d",&p,&x);
		printf("%d\n",sum-a[p]+x);
	}
	return 0;
}
```

---

## 作者：_HMZ_ (赞：2)

### 这道题的标签里有线段树，但是却没人用线段树做？！所以本蒟蒻来水一发。

（虽然橙题用线段树确实有点大材小用）

## 题目大意

joisino 在参加比赛，比赛里有 $n$ 道题，每道题都有做出来的时间。

还有 $m$ 瓶饮料，喝了他之后做 $P_i$ 道题的时候时间会变为 $X_i$ 秒。（雾

对于每一瓶饮料，joisino 想知道在喝了它之后做完所有题的时间总和是多少。

## 解题思路

如果还不会线段树的话，可以到 [线段树模板](https://www.luogu.com.cn/problem/P3372) 看看各位大佬发的题解，学学线段树。

这道题只需要线段树的求和，不需要更改。

由于数据很小，所以可以枚举每一瓶饮料，把做其他题的时间的总和求出来然后再加上

这道题的时间，就可以求出最终的答案了。

## 代码

以下是 AC 代码。

```cpp
#include<iostream>
using namespace std;
int a[100005], n, m, tree[100005];
void build(int now, int l, int r)//线段树的初始化
{
	if (l == r)
	{
		tree[now] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(now * 2, l, mid);
	build(now * 2 + 1, mid + 1, r);
	tree[now] = tree[now * 2] + tree[now * 2 + 1];
}
int query(int now, int l, int r, int x, int y)//线段树的查询操作
{
	if (l > y || r < x)
		return 0;
	if (x <= l && r <= y)
		return tree[now];
	int mid = (l + r) / 2, res = 0;
	res = query(now * 2, l, mid, x, y) + query(now * 2 + 1, mid + 1, r, x, y);
	return res;
}
int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, 1, n);
	cin >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		cout << query(1, 1, n, 1, u - 1) + query(1, 1, n, u + 1, n) + v << endl;
		//当前时间等于 这瓶饮料对应的这道题的 左边时间总和 加上 右边时间总和 加上 喝完饮料的时间
	}
	return 0;
}
```


---

## 作者：Fido_Puppy (赞：2)

## 思路

这题其实只要模拟就行了。

于是，我们先把做题需要的时间总和给求出来。

接着每次输入一种饮料的功能，把做题的时间给替换一下就行了。

```writeln(sum+x2-t[x1]);```

## 代码

为 P 党代言。

```pascal
var
  n,i,sum,m,x1,x2:longint;
  t:array[1..100] of longint;
begin
  readln(n);
  for i:=1 to n do begin
    read(t[i]);
    inc(sum,t[i]);
  end;
  readln(m);
  for i:=1 to m do begin
    readln(x1,x2);
    writeln(sum+x2-t[x1]);
  end;
end.
```
完结撒花！ ^.^

---

## 作者：Zachary_Cloud (赞：2)

## Solution

这道题，我们可以先把每瓶饮料的时间相加，再对于接下来的每个输入进行替换，再输出即可。

~~（其实就是简单的模拟！）~~


## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, t[110], p[110], x[110], sum;
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> t[i], sum += t[i];
	cin >> m; //输入
	for (int i = 1; i <= m; ++i) cin >> p[i] >> x[i], cout << sum - t[p[i]] + x[i] << endl;
   //替换操作，边输入边操作
	return 0;
}
```

---

## 作者：梦游的小雪球 (赞：1)

### 这是一道~~很水~~的纯模拟。
## 梦雪的思路：

-  先计算总和（$ s=\sum_{i=1}^n a_i $），再对应每种饮料，输出被影响后的$s$。

## 你们的最爱：

```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[103],s;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s+=a[i];
	}//输入+累加
	cin>>m;
	while(m--){
		int x,y;
		cin>>x>>y;
		cout<<s+y-a[x]<<endl;
    		//y-a[i]即饮料带来的影响
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

说实话，~~这题真难，太难了~~，
作为一个蒟蒻，就要有蒟蒻的亚子鸭

大概这份代码会比较清凉吧(●´∀｀●)

```python
#include<iostream>
#include<cstdio>
using namespace std;
int ti[100000];
int n;
int tot[100000];int k=0;
int kasita(int a,int b){
	int num=0;
	for(int i=1;i<=n;i++){
		if(i!=a)//小小判断 
		num+=ti[i];
		else//其实只会执行一次、、233 
		num+=b;
	}
	tot[++k]=num;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>ti[i];
	} 
	int m;
	cin>>m;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		kasita(a,b);
	}
	for(int l=1;l<=k;l++){
		cout<<tot[l]<<endl;
	}
	
} 
```

另外其实函数部分也可以改成
```java
int kasita(int a,int b){
	int num=0;
	for(int i=1;i<a;i++){ 
		num+=b;
	}	
	num+=ti[i]; 
	for(int i=a+1;i<n;i++){
		num+=ti[i]; 
	}
	tot[++k]=num;
}
```

望通过，谢谢啦QAQ


---

## 作者：Anakin (赞：1)

这题其实不难，冷静分析一下就极其简单
因为使用第i个饮料对其他没有影响，把所有的时间求和，每次减掉t[i],再加x[i]然后输出就ok
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 100+10
using namespace std;
inline int read(){
	int out=0;
	char c=getchar();
	while(c<48||c>57) c=getchar();
	while(c<=57&&c>=48){
		out=(out<<1)+(out<<3)+c-48;
		c=getchar();
	}
	return out;
}
inline void write(int x){
	if(x>9) write(x/10);
	putchar(x%10+48);
}
int a[MAXN];
int b[MAXN];
int n;
int sum=0;
int main(){
	n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		sum+=a[i];
	}
	int m=read();
	for(int i=1;i<=m;++i){
		int x=read();
		int y=read();
		int ans=sum;
		ans-=a[x];
		ans+=y;
		write(ans);
		putchar(10);
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：1)

看了一遍，没有Pascal的，就发一篇吧！

此题太水，怎么能称为紫题呢？（各人认为应该是橙题）

## 思路
### 1.输入
### 2.算出做所有做题时间的和（不算也没事，不过后期要麻烦一些）
### 3.输入，计算出喝饮料后所有做题时间的和
### 4.输出

接下来献上Pascal代码
```
var a:array[1..100]of longint;
    n,m,s,i,x,y:longint;
begin
 readln(n);
 for i:=1 to n do begin read(a[i]); s:=s+a[i];//求和 end;
 readln;
 readln(m);
 for i:=1 to m do begin readln(x,y); writeln(s+(y-a[x]));//求和之后可以推出公式，更加方便 end;
end.
```

---

