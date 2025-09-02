# ニコニコ文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dwango2015-prelims/tasks/dwango2015_prelims_2

$ 0 $ から $ 9 $ の数字から成る文字列 $ S $ が与えられます。

ある文字列 $ X $ について、$ X=&quot;25&quot; $ または $ X=&quot;2525&quot; $ または $ X=&quot;252525&quot; $ …… というふうに $ &quot;25&quot; $ を何回か繰り返した文字列になっているとき、$ X $ はニコニコ文字列であるといいます。 たとえば $ &quot;25&quot; $ や $ &quot;25252525&quot; $ はニコニコ文字列ですが、$ &quot;123&quot; $ や $ &quot;225&quot; $ はニコニコ文字列ではありません。

あなたの仕事は、文字列 $ S $ について、ニコニコ文字列となるような連続した部分文字列の取り出し方が何通りあるかを答えることです。 文字列として同じであっても、取り出し位置が異なっていれば別々に数えます。

## 说明/提示

### 部分点

この問題には部分点が設定されています。

$ N≦2000 $ を満たすデータセット $ 1 $ にすべて正解すると、$ 30 $ 点が得られます。 追加制約のないデータセット 2 にすべて正解すると、上記のデータセットに加えてさらに $ 70 $ 点が得られ、全体で $ 100 $ 点が得られます。

### Sample Explanation 1

$ S=&quot;2525&quot; $のケースです。部分文字列が $ &quot;25&quot; $ となる取り出し方が $ 2 $ 通り、$ &quot;2525&quot; $ となる取り出し方が $ 1 $ 通りあるので合計 $ 3 $ 通りを出力します。

## 样例 #1

### 输入

```
2525```

### 输出

```
3```

## 样例 #2

### 输入

```
1251251252525```

### 输出

```
8```

## 样例 #3

### 输入

```
25225```

### 输出

```
2```

## 样例 #4

### 输入

```
252252252252252252```

### 输出

```
6```

## 样例 #5

### 输入

```
20061212```

### 输出

```
0```

# 题解

## 作者：亦枫 (赞：1)

## Solution

题意：求出字符串 $ S $ 中，有多少个子串只由 $ 25 $ 组成。

看一眼数据范围，暴力枚举左右端点时间复杂度达到了 $ O(n^3) $ 肯定过不了，那么思考如何快速解决这个问题。

**我们先简化这个问题，有一个只由 $ 25 $ 组成的字符串，求他的子串个数。**

设这个字符串有 $ n $ 个 $ 25 $。

$ 1 $.若 $ n $ 个被选入有只有 $ 1 $ 个子串。

$ 2 $.若$ n-1 $  个被选入有只有 $ 2 $ 个子串。

$ 3 $.若 $ n-2$  个被选入有只有 $ 3 $ 个子串。

以此类推……

则有

$ n $.若 $ 1 $ 个被选入有只有 $ n $ 个子串。

**所以得出规律，一个含 $ n $ 个 $ 25 $ 的字符串有 $ \dfrac{(n+1) * n}{2} $ 个满足题意的子串。**

那么，只要我们求出有几个含 $ 25 $ 的连续的字符串即可。

**Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
ll a[1000005]={},ans=0,tmp=0;//记得开long long ，否则会爆int
int main() {
	cin>>s;
	memset(a,0,sizeof(a));
	for(int i=0;i<s.length()-1;i++){
		if(s[i]=='2'&&s[i+1]=='5'){
			a[i]=a[i+1]=-1;//记录25的个数
			i++;
		}
	}
	for(int i=0;i<s.length();i++){
		if(a[i]==-1){
			tmp++;//记录连续的25的个数
		}
		else if(tmp!=0){
			tmp=tmp/2;//面对一个25tmp加了两次，所以要除2
			ans+=(tmp*(tmp+1)/2);//求和
			tmp=0;//求完和记得将tmp清零
		}
	}
	tmp=tmp/2;
	ans+=(tmp*(tmp+1)/2);
    //tmp可能在最后还不为0，所以在运行一次
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Egg_eating_master (赞：0)

作为一道字符串橙题应该不会太难吧。

一开始看到题面：“这题居然没有过水被隐藏？直接$O(n^3)$枚举$S$的每个子串不就得了么？！”最后看到长度$\le 10^5$的数据范围果断放弃……这道题并没有想象中那么简单。

怎么做？

首先，我们得知道一个~~显而易见的~~定理：如果$S$中有一个子串由$x$个$25$组成，那么从这个子串当中，我们就可以得到$\sum_{i=1}^xi$个$\operatorname{niconico}$字符串。

有了这个结论就非常简单了。

我们设置一个变量$sum$表示最长的以当前位置结尾的、由$25$连接而成字符串中，连续的$25$的个数。扫描一遍$S$，碰到$25sum$就加一，$25$中断了答案$ans$就累加。最后输出$ans$即可。

但是还是有几个小坑，具体见代码。
```
#include<bits/stdc++.h>
#define ll long long
//懒得每次都打一个longlong所以将longlong简写为ll
using namespace std;
string s;
ll ans;
ll sum;//含义已经讲过了
int main(){
	cin>>s;
	s+=' ';//一定要加上一个空格（其他字符也可以）,否则最后的一个25不会累加进去
	for(int i=0;i<s.size();i++){//扫描整个字符串
		if(s.substr(i,2)=="25")sum++,i++;
        //找到了25，sum就加一，i也跳到下一个可能出现25的地方
		else ans+=sum*(sum+1)/2,sum=0;
        //如果没找到，那么ans就累加，一定注意sum要清零
	}
	cout<<ans<<endl;//AT换行万年老坑
	return 0;//拜拜了您嘞
}
```
总结一下，怎么想到这种方法的呢？

首先我们看到数据范围，就知道只能用$O(n)$或$O(n\log n)$的算法。你见过字符串用$O(n\log n)$的么？所以只能扫描一遍字符串。因此想要知道连续的$25$的个数就很自然了。于是，问题迎刃而解。

---

## 作者：SfumatoCannon_ (赞：0)

### 题意翻译

给定一个字符串 $S$ ，求有多少个子串由```25```组成。

$S$ 的长度小于等于 $10^5$.

### Solution

我们考虑这样一个样例：

```cpp
25252525
```

其中子串为```25```的个数：$4$

子串为```2525```的个数：$3$

子串为```252525```的个数：$2$

```25252525```的个数：$1$

所以输出应为：$4+3+2+1=10$

由上不难看出：如果有一个子串由 $n$ 个```25```组成，那么其对答案的贡献为：

$$\sum_{i=1}^{n}i=\frac{(n+1)n}{2}$$

于是问题转化为：统计字符串中由且仅由```25```构成的子串个数。

读入后扫一遍，很容易做到 $O(n)$.

### code

为了使思路更清晰，这里我扫了两遍字符串：

第一遍统计纯由```25```构成的子串并打上标记，

第二遍处理标记，算出对答案的贡献并累加。
***
还有一些要注意的点：

* 本题答案要开```long long```。

* 输出要换行。

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char str[100001];
bool a[100001];	//打标记用
int main()
{
	int i;
	scanf("%s",str);
	for (i=1;i<strlen(str);i++)
		if (str[i]=='5'&&str[i-1]=='2')
   			a[i]=a[i-1]=1;	//由25构成的子串位置打上标记
	long long t=0,ans=0;
	for (i=0;i<strlen(str)+1;i++)
	{
		if (a[i]==1)
			t++;
		else if (t!=0)
		{
			t=t/2;	//由于"25"长度为2，在这里要记得除2
			ans+=t*(t+1)/2;
			t=0;
		}
	}
	printf("%lld\n",ans);
 	return 0;
}
```


---

## 作者：大头leo (赞：0)

### 读题：
这道题简单来说就是让你找一个字符串内有多少个连续25的字串。其实还是蛮简单的，见思路。
### 思路：
- 读入字符串之后，我们从头到尾开始寻找 _25_ ，程序里我使用了 _while_ 循环找，这样在处理连续25的时候相对方便很多。

- 那么找到 _25_ 后怎么办呢？如前些题解所述。如果有 _n_ 个 连续的 _25_ ，那么其中的niconico子串的个数就是 _1+2+3+.....n_ 。

- 理解了上一条后，我们只需要在 _while_ 里安插一个变量，每次循环都加1，计数器再加上这个变量，就完成判断连续niconico字串的操作。（具体见程序）
### 注意点：
- 每次找到 _25_ 后，我们的循环变量 _i_ 就可以加2，继续寻找下一组。

- 输出后一定要换行！否则全wa！~~别问我怎么知道的~~

##### 该讲的都讲完了，下面见程序
### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string a;
int ans,i,j=1;	//ans计数，i、j循环变量 
int main()
{
	cin>>a;
	for(i=0;i<a.size();i++)	//开始寻找 
	{
		j=1;				//每次循环j都要赋初值 
		while(a[i]=='2'&&a[i+1]=='5')		//找到 
		{
			ans+=j;		//计数器累加 
			j++;		//思路及注意点都讲过了 
			i+=2;	
		}
	}
	cout<<ans<<endl;
}

```


---

## 作者：xiaohuang (赞：0)

[更好的阅读体验](https://xiaohuang888.github.io/2019/12/14/%E3%80%8CAT1175%E3%80%8D%E3%83%8B%E3%82%B3%E3%83%8B%E3%82%B3%E6%96%87%E5%AD%97%E5%88%97/)

### Solution

我们可以先把连续的`25`都替换从一个字符，如`a`，然后我们找连续的`25`，每一段`25`都可以用组合数计算出`niconico`的数量。然后累加就可以了。

**坑：注意要开`long long`。**

### Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>

using namespace std;

typedef long long LL;
string st;
int main() {
    cin >> st;
    string b = "";
    for (int i = 0; i < st.length() - 1; i++)
        if (st[i] == '2' && st[i + 1] == '5') b = b + 'a', i++; else b = b + st[i];//将所有的"25"转化为'a'
    b = '1' + b + '1';//防止溢出，添加边界
    LL l = -1, r = 0, ans = 0;//必须要long long
    for (int i = 1; i < b.length() - 1; i++) {
        if (b[i] == 'a' && b[i - 1] != 'a' && l == -1) l = i;
        if (b[i] == 'a' && b[i + 1] != 'a') {
            r = i;
            ans += (r - l + 1) * (r - l + 2) / 2;//计数连续一段的价值
            l = -1;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：αnonymous (赞：0)

这道题目的意思其实就是找到有连续“25”的字符串个数,
一开始暴搜TLE了，这让我觉得这道红题有点东西

暴搜程序：
```cpp
#include <iostream>
#include <string>
using namespace std;
string s,ss,st;
int sn,ans;
int main(){
    int i,j,k;
    cin>>s;
    while(sn+2<=s.length()){
        sn+=2;
        st=st+"25";
        ss=s;
        k=ss.find(st);
        while(k>=0&&k<ss.length()){
            ans++;
            ss.erase(0,k+1);
            k=ss.find(st);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
然后我仔细想了想，如果有连续的n个“25”,则可分解为1+2+3+4…+n个niconico字符串
> 如：2525…………25…25…2525………共1+2个

> 252525………3个25…2个2525…1个252525………共1+2+3个

于是乎，便有了一个AC版本：
```cpp
#include <iostream>
#include <string>
using namespace std;
string s,st="25";
int sn,ans;
int main(){
	int i,j,k;
	cin>>s;
	k=s.find(st);//找到“25”
	while(k>=0&&k<s.length()){//找到的话
		if(k==0)//如果就连接在上个“25”后面
			j++;//ans加上j+1个
		else//如果不在上个“25”后面
			j=1;//重新从1算起
		ans+=j;
		s.erase(0,k+2);//删掉0~现在找到的25中所有的字符
		k=s.find(st);
	}
	cout<<ans<<endl;
	return 0;
}
```

---

