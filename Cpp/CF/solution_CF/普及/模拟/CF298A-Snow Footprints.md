# Snow Footprints

## 题目描述

There is a straight snowy road, divided into $ n $ blocks. The blocks are numbered from 1 to $ n $ from left to right. If one moves from the $ i $ -th block to the $ (i+1) $ -th block, he will leave a right footprint on the $ i $ -th block. Similarly, if one moves from the $ i $ -th block to the $ (i-1) $ -th block, he will leave a left footprint on the $ i $ -th block. If there already is a footprint on the $ i $ -th block, the new footprint will cover the old one.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF298A/67d5fe232964f55b35f1d37315e4e2b333131dd5.png)At the beginning, there were no footprints. Then polar bear Alice starts from the $ s $ -th block, makes a sequence of moves and ends in the $ t $ -th block. It is known that Alice never moves outside of the road.

You are given the description of Alice's footprints. Your task is to find a pair of possible values of $ s,t $ by looking at the footprints.

## 说明/提示

The first test sample is the one in the picture.

## 样例 #1

### 输入

```
9
..RRLL...
```

### 输出

```
3 4
```

## 样例 #2

### 输入

```
11
.RRRLLLLL..
```

### 输出

```
7 5
```

# 题解

## 作者：KK_lang (赞：2)

## 思路

$L$ 代表从右边走过来，走向左；$R$ 代表从左边走过来，走向右。

我们不妨分析一下。

首先，所有的 $L$ 和 $R$ 必须全部挨在一起，不然的话，就一定会存在一段，使得这一段呈：

$1$、```LRL``` 状：$L$ 在两边 $R$ 在中间，此时两个 $L$ 不能同时走到，不成立；

$2$、```RLR``` 状：$R$ 在两边 $L$ 在中间，同理，两个 $R$ 也不能同时走到，不成立。

综上，$L$ 与 $R$ 必须同类挨在一起，呈 ```LR``` 或 ```RL``` 状。

然而，```LR``` 其实是不成立的。

分析一下，在左端有 $L$，右段有 $R$，意为你需要从右边走到最左边同时从左边走到最右边，此时只能满足一个，而另一个会被覆盖不同的脚印，绝对不可能是 ```LR``` 状。

所以，我们总结一下，符合规律的有以下几种：

$1$、全是 $L$，例：```LLLLLL```。此时答案为从最右边走到最左边。

$2$、全是 $R$，例：```RRRRR```。此时答案为从最左边走向最右边。

$3$、左边 $R$、右边 $L$，例如：```RRRRLLL```。此时答案为从 $R$ 第一个到 $R$ 最后一个，或者从 $L$ 最后一个到 $L$ 第一个。我们注意到一句话：```The first test sample is the one in the picture.```，所以两种都可以，我们就用第一种：从 $R$ 第一个走到 $R$ 最后一个就行了。

## AC Code

已经论证了情况数，实现就非常简单。

具体的代码实现，看注释。

```cpp
#include<btis/stdc++.h>
using namespace std;

int main()
{
    string s; // 原雪地脚印
    int Rfst, Rlst, Lfst, Llst, n; 
    // R 的第一个、R 的最后一个；L 的第一个、L的最后一个；s 长度
    cin >> s;
    n = s.size(); // 存长度于 n
    s = " " + 1; // 从 1 开始
    for (int i = 1; i <= n; i++)
        if (s[i] == 'R')
        {
            Rlst = i; // 因为正序最后一个 R 肯定是最后一个，座椅直接覆盖
            if (Rfst == 0) Rfst = i; // 只有前面没有 R 才是第一个
        }
        else if (s[i] == 'L')
        {
            Llst = i; // 与 R同理 
            if (Lfst == 0) Lfst = i; // 与 R 同理
        }
    // 1、没有 L，只有 R，即 L 连第一个都没有
    if (Lfst == 0) cout << Rfst << " " << Rlst << endl;
    // 2、没有 R，只有 L，即 R 连第一个都没有
    else if (Rfst == 0) cout << Llst << " " << Lfst << endl;
    // 3、RRRRLLLL
    else cout << Rfst << " " << Rlst << endl;
    return 0;
}
```

思维题，只要想通了就非常简单了，预处理和简单判断就过了。

---

## 作者：Night_sea_64 (赞：2)

首先我们来想想这个字符串会是什么样子的。

我们先试试，随便移动。发现这个字符串只有 $3$ 种情况，即 $\texttt{RRR}$ 形，$\texttt{LLL}$ 形 和 $\texttt{RRRLLL}$ 形。

怎么可能只有这 $3$ 种呢？

显然不可能有 $\texttt{LLLRRR}$ 形。如果有的话，你必须去 $\texttt{L}$ 连通块的最左侧，也必须去 $\texttt{R}$ 连通块的最右侧。但这两者不能同时进行，你必须先去其中一个，再去另一个。但是这样先去的方向的脚印就会被后去的方向脚印覆盖掉。

我们可以进一步推出没有一串合法的脚印含有 $\texttt{LLLRRR}$ 形的子串。如果一串脚印的连通块个数超过 $2$ 个，必定会含有 $\texttt{LLLRRR}$ 形的子串。所以我们得出结论，肯定只有这 $3$ 种形式的脚印。

就这三种不就好办了？？？

如果是 $\texttt{RRR}$ 或 $\texttt{LLL}$ 形的就直接往同一个方向走。如果是 $\texttt{RRRLLL}$ 形，可以先向左再向右，也可以先向右再向左，随便哪个都行。记录 $\texttt{R}$ 和 $\texttt{L}$ 连通块的左右端点，然后根据情况选他的起点和终点就行了。但是要注意终点的位置还没有踩上脚印。

AC 代码：

```cpp
#include<iostream>
using namespace std;
char a[1010];
int main()
{
    int n,Rl=0,Rr=0,Ll=0,Lr=0;//Rl,Rr,Ll,Lr 分别记录 R 的左右端点和 L 的左右端点。
    cin>>n;
    a[0]='.',a[n+1]='.';
    for(int i=1;i<=n+1;i++)
    {
        if(i<=n)cin>>a[i];
        if(a[i]=='R'&&a[i-1]!=a[i])Rl=i;
        if(a[i]=='L'&&a[i-1]!=a[i])Ll=i;
        if(a[i-1]=='R'&&a[i-1]!=a[i])Rr=i-1;
        if(a[i-1]=='L'&&a[i-1]!=a[i])Lr=i-1;
    }
    //RRR 形
    if(Ll==0&&Lr==0)cout<<Rl<<" "<<Rr+1<<endl;//一直向右
    //LLL 形
    else if(Rl==0&&Rr==0)cout<<Lr<<" "<<Ll-1<<endl;//一直向左
    //RRRLLL 形
    else cout<<Rl<<" "<<Ll-1<<endl;//我选的是先向右再向左
    return 0;
}
```

---

## 作者：LionShiZi (赞：2)

注意看题目 ： 

就是 solar bear 必须走过这格之后才会造成印迹的变化 这点是需要注意的。

结果就只有这三种情况了

（1）RRRRR  从1走到6

（2）LLLLLL 从6走到1

（3）RRRRLLLLL  这种情况我是考虑 第一个R出现的位置为起始位置，第一个L出现的位置为终止位置，这是最终的结果的其中一项。

### 不存在 LLLLRRRR这样的情况
```cpp
#include<bits/stdc++.h>
char s[3000];
using namespace std;
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
         scanf("%s",s);
         int R=0,L=0,posR=n+10,posL=n+10;
         for(int i=0;i<n;i++)
         {
            if(s[i]=='R')
            {   //找到第一个出现的R
               R++;
               if(posR>i)
               {
                  posR=i;
               }
            }
            if(s[i]=='L')
            {   //找到第一个出现的L
               L++;
               if(posL>i)
               {
                  posL=i;           
            }
            }          
         }
         if(L==0){printf("%d %d\n",posR+1,posR+R+1);continue;}    //全是R的情况
         if(R==0){printf("%d %d\n",posL+L,posL);continue;}        //全是L的情况
         printf("%d %d\n",posR+1,posL);                           //第三种情况
    }                          
    return 0;                          
}    
```


---

## 作者：_Maverick_ (赞：1)

## 题意
雪地里有一条路，可以向左走、向右走，每走一步会在这一步的起点留下一个朝向走的方向的脚印，新脚印会覆盖旧脚印，现给出脚印的情况，判断起点和终点
## 思路
如果只有一个方向的脚印，那就是从脚印的一头走到另一头，如果两个方向都有，那一定是若干个 $R$ 以后若干个 $L$ ，那么就以第一个 $R$ 为起点，最后一个 $R$ 为重点就可以了。
## ACcode

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
char ss[1001];
int n, s, t, f1, f2;
int main() {
	cin >> n;
	cin >> ss;
	f1 = 0;
	f2 = 0;
	for (int i = 0; i < n; i++)
		if (ss[i] == 'L')
			f1 = 1;
		else if (ss[i] == 'R')
			f2 = 1;
	if (f1 == 0) {
		for (int i = 0; i < n; i++)
			if (ss[i] == 'R') {
				s = i + 1;
				break;
			}
		for (int i = n - 1; i >= 0; i--)
			if (ss[i] == 'R') {
				t = i + 2;
				break;
			}
	} else if (f2 == 0) {
		for (int i = n - 1; i >= 0; i--)
			if (ss[i] == 'L') {
				s = i + 1;
				break;
			}
		for (int i = 0; i < n; i++)
			if (ss[i] == 'L') {
				t = i;
				break;
			}
	} else {
		for (int i = 0; i < n; i++)
			if (ss[i] != '.') {
				s = i + 1;
				break;
			}
		for (int i = s - 1; i < n - 1; i++)
			if (ss[i] != ss[i + 1]) {
				t = i + 1;
				break;
			}
	}
	cout << s << " " << t << endl;
	return 0;
}
```

---

## 作者：QingDeng_Star (赞：1)

## 思路
妥妥的思维题。


```L``` 是从右到左，```R```  是从左到右。手玩一遍样例，易得 ```L``` 和 ```R``` 必须要挨在一起才可以走出来，就是 ```LR``` 和 ```RL```，还有全是 ```L``` 的 ```LL``` 和全是 ```R``` 的 ```RR``` 这四种情况，但是如果深入思考，会发现 ```LR``` 是不可能的，因为这代表你要同时从右到左，从左到右，而脚印会覆盖，所以走到最后就变成了 ```LL``` 或者是 ```RR```。分情况讨论过后，接下来就简单了。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int main()
{
    int n,l1,l2,r1,r2;//分别代表 L,R 的开头和结尾
	cin>>n;
	cin>>s;
    for(int i=1;i<=n;i++)
    {
		if(s[i]=='R')//R 的情况
       	{
        	r2=i//结尾
            if(l2==0)
        		l2=i;//开头
		}
		if(s[i]=='L')
        {
        	r1=i； 
			if(l1==0)
				l1=i;
		}
	}
	if(r1==0)
    {
		cout<<l2<<" "<<l1-1;
		return 0;
	}
	if(l1==0)
    {
		cout<<l2<<" "<<r2+1;
		return 0;
	}
	cout<<l1<<" "<<r2+1;
	return 0;
}
```
如有错误，请大佬多多指出。

完结散花！

---

## 作者：Hutao__ (赞：0)

~~一道大水题~~

应该是 Special Judge 的，因为在 $\texttt{RRRLLL}$ 的情况下可以是 1 3，也可以是 4 3。

### 思路


有三种可能：`LLL`，`RRR`，`RRL`。

为什么没有 `LLR`：因为你要从最左边走到最右边，那么 $\text{R}$ 一定会被覆盖。

如果是 `LLL`：输出第一个 $\texttt{L}$ 和最后一个 $\texttt{L}$ 所在的位置。

如果是 `RRR`：输出最后一个 $\texttt{R}$ 和第一个 $\texttt{R}$ 所在的位置。

如果是 `RRL`：输出最后一个 $\texttt{R}$ 和第一个 $\texttt{R}$ 所在的位置。（当然，从最后一个 $\texttt{L}$ 到最后一个 $\texttt{R}$ 也可以）

###  代码




```cpp
#include<bits/stdc++.h>
using namespace std;
int n,rs,re,ls,le;//R的开始，R的结束，L的开始，L的结束
string s; 
int main(){
	cin>>n>>s;
	s=' '+s; //从第一位开始
	for(int i=1;i<=1+n;i++){
		if(s[i]=='R'){//如果是R
			re=i;//记录结尾
			if(rs==0)rs=i;//如果前面没有，就记录在开头
		}
		 if(s[i]=='L'){
			le=i;//同上
			if(ls==0)ls=i;//同上
		}
	}
	if(le==0)cout<<rs<<' '<<re;//如果只有R
	else if(re==0)cout<<le<<' '<<ls;//如果只有L
	else cout<<rs<<' '<<re;
	return 0;//完美收工~
}

```

---

## 作者：_Violet_Evergarden (赞：0)

看到题解有些空缺，来发一发。

# 思路
初看这题还是有些懵的，然而经过简单的样例模拟后我们会发现一个很容易得到的结论，就是只有三种情况是可行的，分别为 $LL$ 型，$RL$ 型和 $RR$ 型。然后我们只用对这三种情况分类讨论出一种始终可行的方案即可。话不多说，请见代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char a[100000001];
int flag;
int flag1;
int flag2;
int fl,fr,ll,lr;
int main()
{
	cin>>n;
	cin>>a+1;
	for(int i=1;i<=n;i++){
		if(a[i]=='R'){
			if(!fr){
				fr=i;
			}
			lr=i;
		}
		if(a[i]=='L'){
			if(!fl){
				fl=i;
			}
			ll=i;
		}
	}
	if(!fr){
		cout<<ll<<" "<<fl-1;//从最右边走到最左边 
		return 0;
	}
	if(!fl){
		cout<<fr<<" "<<lr+1;//从最左边走到最右边 
		return 0;
	}
	cout<<fl<<" "<<lr+1;//从最左边的L开始走，走到最右边后折回至最左边，然后向右走走到最右边的R 
	return 0;
} 
```


---

