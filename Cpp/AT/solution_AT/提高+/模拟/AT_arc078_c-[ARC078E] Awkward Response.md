# [ARC078E] Awkward Response

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc078/tasks/arc078_c

**これはインタラクティブな問題です。**

すぬけくんはお気に入りの正の整数 $ N $ を持っています。あなたは 「$ n $ はお気に入りの正の整数か？」と最大 $ 64 $ 回すぬけくんに質問することができます。 $ N $ を特定してください。

すぬけくんはひねくれ者なので「$ n $ はお気に入りの正の整数か？」と質問されたとき、$ n $ が以下の $ 2 $ つの条件のどちらかを満たすとき Yes と、それ以外のとき No と答えます。

- $ n\ \leq\ N $ かつ $ str(n)\ \leq\ str(N) $を満たす
- $ n\ >\ N $ かつ $ str(n)\ >\ str(N) $ を満たす

ここで、$ str(x) $ は正の整数 $ x $ を十進表記(先頭に $ 0 $ をつけない)の文字列として表したものです。例えば $ str(123)\ = $ `123`，$ str(2000) $ = `2000` です。 なお、この問題において文字列同士は辞書順で比較されます。例えば `11111` $ < $ `123`，`123456789` $ < $ `9` が成立します。

### Input &amp; Output Format

各質問は、標準出力に以下の形式で出力せよ：

> ? $ n $

ここで $ n $ は $ 1 $ 以上 $ 10^{18} $ 以下の整数でなければならない。

次に、質問の答えが標準入力から以下の形式で与えられる：

> $ ans $

ここで $ ans $ は `Y` または `N` である．`Y` ならば、質問の答えが Yes であることを、`N` ならば No であることを示す。

最後に、答えを以下の形式で出力せよ：

> ! $ n $

ここで $ n=N $ でなくてはならない。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{9} $

### ジャッジ

- **出力のあと、標準出力を flush せよ。**従わない場合 `TLE` の可能性がある。
- 答えを出力した後、プログラムをすぐに終了せよ。従わない場合のジャッジの挙動は定義されていない。
- 出力の答えが間違っている場合の挙動は定義されていない(`WA` とは限らない)。

### 入出力例

これは $ N=123 $ のときの入出力例です。

 Input Output  `? 1` `Y`   `? 32` `N`   `? 1010` `N`   `? 999` `Y`   `! 123`- $ 1\ \leq\ 123 $ かつ $ str(1)\ \leq\ str(123) $ なので答えは Yes です
- $ 32\ \leq\ 123 $ ですが、$ str(32)\ >\ str(123) $ なので答えは No です
- $ 1010\ >\ 123 $ ですが、$ str(1010)\ \leq\ str(123) $ なので答えは No です
- $ 999\ \geq\ 123 $ かつ $ str(999)\ >\ str(123) $ なので答えは Yes です
- $ N $ は $ 123 $ であると $ 4 $ 回の質問で回答できたため正解となります

# 题解

## 作者：yqbylty (赞：2)

### 解题思路：

首先我们考虑确定数字$N$的位数，怎么确定数字$N$的位数呢，我们定义一个最大值$10^9$，然后一位一位删减，因为交互库返回$Y$要满足值的大小关系和字典序大小关系要相同，所以当交互库返回$Y$的时候，我们就确定下来$N$的位数了。

然后怎么确定$N​$的具体值呢？二分答案就好了。

#### Code：

```cpp
/*Program from Luvwgyx*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
char s[10];
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}
void write(int x){print(x);puts("");}
void query(ll  x){printf("? %lld\n",x);fflush(stdout);scanf("%s",s);}
int main(){
    int x=1e9;query(x);
    if(s[0]=='Y'){
        for(int i=9;i;i--){
            query(x-1);
            if(s[0]=='N')break;
            x/=10;
        }printf("! %d\n",x);
        return 0;
    }//特判类似10000这种情况
    for(int i=9;i;i--){
        x/=10;query(x);
        if (s[0]=='Y')break;
    }int l=x+1,r=x*10-1,ans;
    while(l<=r){
        ll mid=(l+r)>>1;query(mid*10);
        if(s[0]=='Y')r=mid-1,ans=mid;
        else l=mid+1;
    }printf("! %d\n",ans);
    return 0;
}
```

---

## 作者：SunsetSamsara (赞：1)

## 题意

给定一个数字 $N$，要你通过若干次询问得到 $N$。

每次可以询问一个数字 $x$，会得到：

+ 当 $x \leqslant N$ 时，返回 $str(x) \leqslant str(N)$
+ 当 $x > N$ 时，返回 $str(x) > str(N)$

其中 $str(x)$ 表示 $x$ 转化为字符串。

## 分析

可以发现，要先确定数字的位数才能快速地找到这个数。我们发现，数据范围满足 $N \leqslant 10^9$，于是我们就从 $10^9$ 开始，答案为 $Y$ 时排除 $10^x$ 的情况（特判，询问 $99..9$ 类型的数判断位数找到结果），就可以用查询 $10^9, 10^9,...,1$ 的方式找到这个数的位数了。

得到位数，意味着我们得到了这个数的上限和下限。接下来进行二分。这时，我们需要的从数大小变成了数的字典序大小（因为位数相同）。但是，这个大小的条件严重地影响了我们确定这个数。于是，我们需要让大小关系定下来，而不影响字典序。

不难发现，上限一定比下限的 $10$ 倍小，而 $str(A)$ 与 $str(B)$ 的字典序关系和 $str(10^x A)$ 与 $str(10^x B)$ 的字典序关系是一样的。于是，我们就可以通过查询 $str(10x)$ 的方法进行二分了。

## 代码

```cpp
#include <stdio.h>
#define lld long long
char s[100010];
void query(lld x){printf("? %lld\n",x);fflush(stdout);scanf("%s",s);} // 题目的自带询问 API 
int main() {
	int res = 1e9; // 从上限 10^9 开始 
	query(res);
	if (s[0] == 'Y') { // 特判 
		for (int i = 9; i; -- i) {
			query(res - 1); // 通过询问 999...9 类型的数确定 10^x 
			if (s[0] == 'N') break;
			res /= 10;
		}
		printf("! %d\n", res);
	} else {
		for (int i = 9; i; -- i) {
			res /= 10, query(res); // 确定位数 
			if (s[0] == 'Y') break;
		}
		int l = res + 1, r = res * 10 - 1, ans, mid;
		for (; l <= r; ) { //二分 
			mid = (l + r) >> 1;
			query(mid * 10ll); // 乘上 10，不改变字典序关系 
			if (s[0] == 'N') l = mid + 1;
			else r = mid - 1, ans = mid;
		}
		printf("! %d\n", ans);
	}
}
```

---

## 作者：hh弟中弟 (赞：0)

首先肯定要知道这个数有多少位，可以问 $10^k$ 来解决，对于 $k>\lg n$，必有询问 $10^k$ 返回 $\text{N}$，否则有 $n=10^x$，对于这种特殊情况，可以问 $2\times 10^k$ 来解决，对于 $k<\lg n$，必有询问 $2\times 10^k$ 返回 $\text{N}$，否则 $n=1$。\
判完这种特殊情况后考虑从高到低确认 $n$ 的每一位，设 $ans$ 表示已经确定的数，那么肯定是要问与 $n$ 位数不同的数，否则一定会返回 $\text{Y}$，考虑询问 $10(ans+x\times 10^k)+10^{k+1}-1$，前面的字典序相同，后面所有数都为 $9$，这时如果返回 $\text{N}$ 则表示询问的这一位小于 $n$ 的这一位，可以通过二分得出这一位的数，如果没有合法的，则说明这一位是 $0$。\
总次数不会超过 $60$ 次。\
[record](https://atcoder.jp/contests/arc078/submissions/61670218)

---

## 作者：skyskyCCC (赞：0)

## 前言。
远古 ARC 题选做。这是一道神神奇奇的交互题。
## 分析。
只让询问 $64$ 次，如果我们直接询问然后去判断，显然对于绝大部分的数据都会被卡掉。所以我们需要去考虑缩小范围。仔细思考一下发现，我们可以先把这个数的位数确定下来，字典序显然构造一下就可以完成。

所以我们先一通询问确定位数，因为数据范围的限定，所以显然我们询问不了几次，所以还剩下许多的询问次数。考虑从 $1$ 开始往后一直加 $0$ 直到返回 $N$ 了说明位数超了，因为对于序列 $10000\ldots$ 来说，它一直是字典序最小的，所以如果字典序和数字顺序不匹配说明字典序小了而数字顺序大了。那么如果位数确定了，则就在这个位数的这些一定的数中找就行了。显然我们可以知道我们询问的数和 $N$ 的大小关系，这显然就是二分答案。考虑如果在中间值后面加个 $0$ 那么这个数的字典序，这时就是数字的顺序。而实际的中间值乘 $10$ 的数字顺序肯定是大于，所以通过这个判断就可以找到数字的大小关系，如何一步步缩小数据范围，然后找到答案。显然我们二分的过程，在极限数据下对于 $64$ 仍是可以完成的。

但是事实上，如果这个数字是 $1000\ldots$ 的话，我们因为将它作为的一个输入条件，所以会得出错误答案，所以还需要特判一下。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
long long x=1;
long long l,r,mid,ans;
char ch[10];
bool ask(long long x){
    cout<<"? "<<x<<"\n";
    cin>>ch;
    if(ch[0]=='Y'){
    	return 1;
	}
	else return 0;
}
int main(){
    if(ask(1e9)){
        x=1e9;
        for (int i=9;i>=1;i--){
            if(!ask(x-1)){
                break;
            }
            x/=10;
        }
        cout<<"! "<<x<<"\n";
        return 0;
    }
    while(ask(x)){
        x*=10;
    }
    x/=10;
    l=x;
	r=x*10-1;
    while(l<=r){
        mid=(l+r)>>1;
        if(ask(mid*10)){
            r=mid-1;
            ans=mid;
        }
		else{
            l=mid+1;
        }
    }
    cout<<"! "<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

