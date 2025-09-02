# [ARC006C] 積み重ね

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc006/tasks/arc006_3

 高橋君はもう大人なので、親元を離れて一人暮らしをすることにしました。トラックから引越し先の部屋へと荷物のダンボールを運びたいのですが、部屋の床がダンボールで埋まってしまうと、今日高橋君が寝るための布団がひけません。  
 そこで、$ 1 $ 箱ずつ広げて置くのではなく、ある程度ダンボールを積み重ねた山を作ることにしました。しかし、ダンボールには重さが決まっており、下にあるダンボールよりも重いダンボールを上に積み重ねると下のダンボールが潰れてしまいます。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc006_3/330a155330da3a362b0b8091145394d207d35d61.png)図：下にあるダンボールは上にあるダンボール以上の重さでなければならない

 

   
 トラックから運ぶ順にダンボールの重さが与えられるので、ダンボールを潰さないような積み重ね方を考えなさい。そして、その積み重ねた山の個数が最小となる場合の山の個数を求めなさい。 入力は以下の形式で標準入力から与えられる。 > $ N $ $ w_1 $ $ w_2 $ : : $ w_N $

- 入力は $ N+1 $ 行ある。
- $ 1 $ 行目には、ダンボールの個数を表す整数 $ N(1≦N≦50) $ が与えられる。
- $ 2 $ 行目からの $ N $ 行には、$ i+1(1≦i≦N) $ 行目に $ i $ 番目に運ぶダンボールの重さを表す整数 $ w_i(1≦w_i≦100,000) $ が与えられる。

 ダンボールを順番に運び、上のダンボールが下のダンボールと同じ重さまたはそれよりも軽くなるように積み重ねたときに、できるダンボールの山の数の最小値を標準出力に $ 1 $ 行で出力せよ。  
 なお、最後には改行を出力せよ。 ```

5
4
3
1
2
1
```

 ```

2
```

- 下図の例の順に積み重ねると、$ 2 $ つのダンボールの山ができる。
- $ 3 $ 番目のダンボールの次に重さ $ 2 $ のダンボールをその上に重ねることはできないので $ 1 $ つの山にすることはできず、最小は $ 2 $ となる。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc006_3/5cdad1a3c2b4df6c6e3065e4cf34b9c2180d2f93.png)

 ```

7
93
249
150
958
442
391
25
```

 ```

3
```

- 下図の形に積み重ねると、山の数は $ 3 $ となる。
訂正：下図の225のダンボールは25の誤りです。申し訳ありません。


 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc006_3/87e99baa40b995194b9f08a6b6727576d861b3de.png)

 ```

4
100
100
100
100
```

 ```

1
```

- 同じ重さのダンボールは積み重ねられるので、$ 1 $ つの山にすることができる。
 
```

6
5
10
15
20
25
30
```

 ```

6
```

- どのダンボールも前に運んだダンボールの上に重ねられないので、$ 1 $ つも積み重ねることができない。
- したがって、$ 6 $ つの山が最小となる。
 
```

15
3
1
4
1
5
9
2
6
5
3
5
8
9
7
9
```

 ```

6
```

- 下図のように積み重ねると最小となる。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc006_3/6ff699ef802388c8a1126c225e6825673732bcea.png)

# 题解

## 作者：liuyi0905 (赞：6)

## AT_arc006_3题解：
**题目大意：**

高桥先生有$\ n\ $个行李，要把行李堆在房里，如果一个行李上面的行李比他重，就会压坏他。求出至少要放多少堆。

**思路：**

可以用一个数组存每一堆最上面的元素，每读入一个行李重量，在循环所有对顶端的元素，如果可以放，就将那一堆的顶端元素替换掉；如果不能放，就新开一堆。最后输出数组元素个数。

**注意事项：**
1. 要先将第一堆初始值赋一个极大的值，否则会直接开第二堆。
2. AT 的题最后一定要输出换行。

**代码：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,m=1,x[10005];
//m是记录一共有多少堆
int main(){
    x[1]=1e9;
    cin>>n;
    for(int i=1;i<=n;i++){
        bool flag=false;
        cin>>a;
        for(int j=1;j<=m;j++)
            if(a<=x[j]){x[j]=a,flag=1;break;}//放在第j堆上
        if(!flag)m++,x[m]=a;
        //开一个新的堆
    }
    cout<<m<<"\n";//十年AT一场空，不输换行见祖宗
    return 0;
}
```

---

## 作者：zjyqwq (赞：6)

### AT217 题解
本人因为理解错题意而惨遭保龄，已改好。有感而发。

Pascal题解哦！

------------

首先，我要提醒大家，本题翻译疑似有误，请到 [这里](https://atcoder.jp/contests/arc006/tasks/arc006_3)去真正理解题意。


------------
#### 题意解释
根据输入顺序去放置物品。第 $i$ 个物品可以放置在 $1$~$i$-$1$ 的物品上面，但是不能放在  $i$+$1$~$n$ 的物品上面。当一个物品的上面有一个物品比他大的话，这个物品就会被压成奥利给。所以，第 $i$ 个物品如果在前 $i$ 个物品上都放不上去的话，就得单独放一堆。


------------

#### 注意事项
- 还是那句话，AT输出要换行。


------------
#### 帮助理解题意
如果还是不懂题意，没关系，~~我刚开始也不太懂~~，可以借助样例和机翻来理解。

说实在的，Google的机翻都比本题的翻译强。

来几组样例。

###### 样例输入1
```
5
4
3
1
2
1
```
###### 样例输出1
```
2
```
###### 样例输入2
```
7
93
249
150
958
442
391
25
```
###### 样例输出2
```
3
```

###### 样例输入3
```
4
100
100
100
100
```
###### 样例输出3
```
1
```
[Google的Chrome机翻](https://s3.ax1x.com/2021/03/14/60SXAU.png)


------------
#### 代码
```Pascal
var//Pascal来一发！！
i,n,x,j,t:longint;//定义一些杂七杂八的整型变量
p:boolean;//一个哨兵，用来判断用不用单独开
dx:array[0..1000000]of longint;//dx[i]表示第i号堆当前最上面的那个
 begin
  readln(n);//物品的个数
  for i:=1 to n do//一个循环，边读边处理
   begin
    readln(x);p:=false;//开始放置，p为哨兵
    for j:=1 to t do//循环跑一遍，看看可不可以放
     if dx[j]>=x then
      begin
       p:=true;
       dx[j]:=x;
       break;//如果可以放，那就将p标记为true，并将最上面的物品大小更新
      end;
    if not p then begin inc(t);dx[t]:=x; end;//放不了，另开一个堆。并且更新堆的数量
   end;
  write(t);//输出堆的数量
 end.//结束
```


------------

码字不易，点个赞呗![kel](https://cdn.luogu.com.cn/upload/pic/62226.png)

---

## 作者：Deuteron (赞：2)

#### 题意：你有 $n$ 个物品，你需要按照读入顺序去放置物品。
#### 每一堆的物品重量必须是**递减的**，即底部最大，顶部最小。

~~好像原来的题意有亿点问题~~

## solution:
按照贪心的思想去操作。

由于我们只关心堆顶上的物品的重量，所以只用一个数组存储即可。

我们考虑每新读入一个物品，进行以下操作：

从第一个位置开始，如果有一个位置的堆顶的值 $>$ 这个值就将其加入此堆中，更新堆顶。

注意，这个算法成立的条件是各个堆顶的值单调减。

这是没有问题的，因为当只有一个堆时，明显是单调减的

而加入物品的操作**并不会**破坏单调性。

~~不放心的话Sort一遍也可以，反正也不会超时~~

否则，这个物品的值比其他堆顶都小，新开一个堆。

最后只需要输出堆的个数 $T$ 即可。

## code:
```cpp
#include<iostream>
using namespace std;
const int N=2e5+5;
int n;
int a[N],t;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int q;
        cin>>q;//输入箱子重量
        int fl=0;//初始化
        for(int j=1;j<=t;j++){
            if(a[j]>=q){//可以相等
                a[j]=q;//更新堆顶的值
                fl=1;//标记
            }
            if(fl) break;//只能更改一次
        }
        if(!fl) a[++t]=q;//如果都无法更新，新建一个堆
    }
    cout<<t<<endl;//输出堆数
    return 0;
}
```


---

## 作者：yhylivedream (赞：1)

看到没有人用 vector 做的。

## vector 基本操作

1. `vector <Type> vec` 新建一个储存类型为 Type 的向量（vector）。

1. `vec.push_back(num)` 把元素 num 添加到向量末尾。

1. `vec.pop_back()` 删除向量末尾的元素。

1. `vec.size()` 返回向量的大小。

1. `vec.clear()` 清空向量中的元素。

遍历vector跟遍历数组几乎一模一样。

## 思路

定义一个向量 $A$ 存每个行李堆顶的重量，每输入一个行李的重量，就遍历一遍 $A$，如果当前重量比 $A_i$ 小，就将 $A_i$ 设为当前重量，否则将当前重量放入向量中，新开一个行李堆。

## 注意

1. 向量（vector）要用 `#include <vector>` 头文件。

1. 要在向量放入一个极大值，以保证第一个重量一定能放到第一堆中。

1. AtCoder 的题最后一定要输出换行啊。

## 代码

```cpp
#include <iostream>
#include <vector>
using namespace std;
vector <int> v;//定义vector 
int a[500005], n; 
int main(){
	cin >> n;
	v.push_back(1e9); 
	for(int i=1; i<=n; i++) cin >> a[i];
	for(int i=1; i<=n; i++){
		bool p = false;
		for(int j=0; j<v.size(); j++){//遍历vector 
			if(v[j] >= a[i]){
				v[j] = a[i], p = true;//更新元素 
				break;
			}
		}
		if(!p) v.push_back(a[i]);//新开一个行李堆 
	}
	cout << v.size() << "\n";//输出行李堆的个数 
	return 0;
}
```

点个赞吧，![](//图.tk/q) ![](//图.tk/q) ![](//图.tk/q)

---

## 作者：cjZYZtcl (赞：1)

## AT217 積み重ね 题解
### 题目大意
按顺序输入 $n$ 个行李，一些行李可以从下到上由重到轻叠成一堆，问最少能叠几堆。

### 思路
这题是贪心题。

由于题目说按照输入顺序放置行李，所以我们用一个数组记录每一个行李堆最顶上的那一个的重量，每输入一个数，就按照堆顶从轻到重的顺序和所有堆顶比较（因为如果某一个堆顶可以放置当前行李，那么更重的堆顶就可以放更重的行李），如果能放置，那么就放在那个堆顶，否则新建一个堆，然后输入下一个数。

按照堆顶从轻到重的顺序可以用排序实现。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = 0, x;
	bool p;
	for(int i = 1; i <= n; i++){
		x = read();
		p = true;
		for(int j = 1; j <= m; j++){
			if(x <= a[j]){
				p = false;
				a[j] = x;
				break;
			}
		}
		if(p == true){
			a[++m] = x;
		}
	}
	write(m);
	putchar('\n');
}
```


---

## 作者：Stars_visitor_tyw (赞：1)

## AT_arc006_3 積み重ね solution
### 题目大意：
高桥君有 $n$ 个行李，他要把行李一个一个放进房中并且堆成堆，在保证一堆行李的重量是从重到轻放置的前提下问最少需要堆多少堆。
### 思路：
这题是一道不错的贪心题。我们用一个数组记录每一堆堆顶也就是最轻的元素，每放入一件行李，就遍历这个数组，如果发现有一堆堆顶比这件行李要重，则把行李放置到这一堆去，并更新这一堆的堆顶重量。但如果没有比这件行李要重的行李便新开一堆，并把这件行李的重量当成堆顶记录，最后看一共有多少堆即可。

### 温馨提示：
1. 记得把计数器定为 0.
2. 岛国题要换行！！！

### 大家最期待的代码环节：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n ,cnt=0, d[10005];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	int a;
        bool flag=false;
        cin>>a;
        for(int j=1;j<=cnt;j++)
        {
            if(a<=d[j])
            {
            	d[j]=a;
               flag=1;
               break;
            }
        }
        if(flag==0)
        {
        	cnt++;
        	d[cnt]=a;
        }
    }
    cout<<cnt<<endl;
    return 0;
}

---

## 作者：FallingFYC_ (赞：0)

# [原题](https://www.luogu.com.cn/problem/AT_arc006_3)
这题太淼了，评橙都没问题……

---
### 思路
一眼贪心。

定义一个数组存储每个行李堆堆顶的行李的重量，命名为 $t$ 数组，每次输入 $w_i$ 时遍历一遍 $t$，如果发现 $w_i$ 小于等于 $t$ 中的某一项，就将这一项设为 $w_i$，并退出循环，若遍历完没有发现 $w_i$ 小于等于 $t$ 中的某一项（$w_i$ 无法放置在任意一堆上），那么就需要在新建一个堆。

注意：
1. $t$ 数组的第一项要初始化成一个极大值，以便在堆放第一个行李时能创建一个新的堆。
2. 换行！

---
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , w , t[55] = {0 , (int)1e5 + 5} , ans;
int main()
{
    cin >> n;
    for (int i = 1 ; i <= n ; i++)
    {
        cin >> w;
        bool flag = false;
        for (int j = 1 ; j <= ans ; j++)
            if (w <= t[j]) {t[j] = w; flag = true; break;}
        if (!flag) t[++ans] = w;
    }
    cout << ans << endl;
    return 0;
}
```
[评测记录，~~我竟然错了一次~~](https://www.luogu.com.cn/record/list?pid=AT_arc006_3&user=923403&page=1)

---

## 作者：nbtngnllmd (赞：0)

## 题意：

已知会有 $n$ 个箱子，会按照从先到后的顺序排列，第 $i$ 个箱子的重量为 $w_i$，现在要把箱子堆积起来，要满足上面的箱子重量必须小于等于下面箱子的重量，否则将会压烂箱子，如果大于下面箱子重量的需要另起一堆，求最小会有几堆箱子。


------------

## 思路：
不难看出此题为一道贪心题，读懂题后我们可以简化一下题意：
问我们如果每堆箱子都必须从大到小进行排列安放，至少会有几堆箱子。

没有必要定义数组来表示每个箱子的重量，该题重点是每次放完箱子后最上面的箱子的质量，可以直接用 $w$ 来表示箱子的重量，然后每次循环完成后更新最大承受重量。


------------
## 核心部分

首先第一个箱子肯定会先堆成第一堆，因此我们可以用一个数组 $a$ 来模拟，先输入第一个箱子重量，把 $w$ 的值赋给 $ a_1$。


------------


```cpp
int n,w,sum = 1,ans = 1;cin>>n;
	bool b ;//定义b判断是否有比该箱子质量更大的箱子
	cin>>w;
	a[sum] = w;	
```


------------


然后从 $2\sim n$ 输入该箱子的重量，然后与每堆箱子可承受的最大重量进行比较。如果小于等于，就可以把可承受重量最大值更新为 $w$，反之则增加一堆箱子，值赋给新一堆箱子可承受重量的最大值。

循环完成再输出答案换行即可。


------------

```cpp
for(int i = 2 ; i <= n ; i++ ) {
		cin>>w;
		b = false;//赋初值
		for(int j = 1 ; j <= sum ; j++ ) {
			if(w <= a[j]) {
				a[j] = w ;
				b = true;
				break;
			}
		}
		if(b==false ) {//如果为假，则答案增加
			ans++;
			a[++sum] = w; 
		}
}
```

------------
最后奉上完整代码，仅供参考。

------------
## 代码：
```cpp
#include<bits/stdc++.h>

using namespace std;
const int Maxn = 100010;
int a[Maxn];
int main(){
	int n,w,sum = 1,ans = 1;cin>>n;
	bool b ;
	cin>>w;
	a[sum] = w;	
	for(int i = 2 ; i <= n ; i++ ) {
		cin>>w;
		b = false;
		for(int j = 1 ; j <= sum ; j++ ) {
			if(w <= a[j]) {
				a[j] = w ;
				b = true;
				break;
			}
		}
		if(b==false ) {
			ans++;
			a[++sum] = w; 
		}
	}
	cout<<ans<<endl;
	return 0;
}
```





 

---

## 作者：FreedomKing (赞：0)

# 有点水的题
[注：blog 食用更佳](https://www.luogu.com.cn/blog/531806/AT217)

------------
### 题目大意
根据输入顺序去放置物品。第 $i$ 个物品可以放置在 $1$~$i$-$1$ 的物品上面，但是不能放在 $i$+$1$~$n$ 的物品上面。当一个物品的上面有一个物品比他大的话，这个物品就会被压成奥利给。所以，第 $i$ 个物品如果在前 $i$ 个物品上都放不上去的话，就得单独放一堆。

参考 [$\color{Green}{2009ZJY}$](https://www.luogu.com.cn/user/303025#main) 大佬的[题意解释](https://www.luogu.com.cn/blog/20090703zjy/solution-at217)
### 思路
我们可以以一个数组 $a$ 来模拟每一堆顶上的物品，以 $t$ 来指向第 $a_t$ 堆的顶上的物品，进行以下操作：
- 如果 $x$ 小于等于 $a_t$，那么就更新 $a_t$ 为 $x$，即``a[t]=x``；
- 如果 $x$ 大于 $a_t$，那么就要另起一堆开始堆叠，即``a[++t]=x``。

最后输出 $t$ 即可。

坑点：$At$ $Coder$ 的题必须要**换行**！

------------
[AT217 積み重ね](https://www.luogu.com.cn/problem/AT217)
### AC Code:
```cpp
#include<bits/stdc++.h>//不用万能头也可以，但个人觉得万能头方便。
#define int long long//保险起见。
using namespace std;
int a[1000005],n;
bool f;//用来标记，后面有用途。
inline int read(){//快读。
	register int x=0,ch=getchar(),t=0;
	if(ch=='-') t=1;
	if(ch>='0'&&ch<='9') x=ch-'0';
	while((ch=getchar())>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48);
	return t?-x:x;
}
inline void write(register int x){//快写。
    if(x<0){putchar('-');x=-x;}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
signed main(){
	int t=0,x;//如果不定成局部变量变量名会和快读的冲突。
	n=read();//读入"n"。
	for(int i=1;i<=n;i++){
		x=read();//读入"x"。
		f=1;//初始化得有
		for(int j=1;j<=t;j++){
			if(x<=a[j]){//判断"x"是否可以堆叠在这一堆。
				f=0;//标记一下。
				a[j]=x;//更新这堆里最轻的。
				break;//结束本次循环。
			}
		}
		if(f==1) a[++t]=x;//另开一堆。
	}
	write(t);//输出"t"。
	putchar('\n');//切记要换行！
	return 0;//好习惯。
}
```

---

