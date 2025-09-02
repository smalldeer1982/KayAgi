# 寿司タワー

## 题目描述

寿司塔

一个寿司由一个米饭和一个菜组成。
现在想用N个寿司来做寿司塔。（包含N个米饭和N个菜）

装1个寿司的方法有以下3种。
原封不动:按米饭、菜的顺序。
翻过来:按照菜、米饭的顺序。
拆开装:分开米饭和菜，分别装。

例如，想把3个寿司从下面开始依次装成“菜、米饭、菜、菜、米饭、米饭”的寿司塔，可以按以下顺序。
1、把一个寿司拆开，装上菜。
2、直接装一个寿司。
3、把一个寿司翻过来装。
4、装上留下的白米饭。
因为拆开寿司很费工夫，所以想尽量减少拆开寿司的个数。 

求完成目标寿司塔需要拆开的寿司个数的最小值。

## 样例 #1

### 输入

```
3
101100```

### 输出

```
1```

## 样例 #2

### 输入

```
5
0000111011```

### 输出

```
3```

# 题解

## 作者：亦枫 (赞：3)

## Solution

题意可以简化为给你**一个长度为 $ 2n $ 的 $ 01 $ 字符串，其中 $ 0 $ 的个数和 $ 1 $ 的个数相等**。

现在以 $ 01 $ 或 $ 10 $ 为单位，从这个 $ 01 $ 字符串拿走尽可能多的 $ 01 $ 或 $ 10 $ ，**求出余下的字符还能构成几个 $ 01 $ 或 $ 10 $ 串**。

那么我们只要对这个 $ 01 $ 字符串进行处理即可。

**Code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
string s;
int n,tmp;
int main() {
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<s.length();i++){
		if((s[i]=='0'&&s[i+1]=='1')||(s[i]=='1'&&s[i+1]=='0')){//处理出可以拿出几个01串
			i++;
			tmp++;//拿走的个数就++
		}
	}
	printf("%d\n",n-tmp);//拿走了tmp个那么就剩下为n-tmp个
	return 0;
}
```


---

## 作者：朱屹帆 (赞：3)

### 题目：[AT1578 寿司タワー](https://www.luogu.com.cn/problem/AT1578)
### 题意：这一题翻译讲的不是很清楚，我来翻译一下：
给你一个数$n$和长度为$2*n$的字符串，由$0$和$1$组成。

其中寿司由两个不一样的字符$0$和$1$组成。

但字符串不一定全是寿司，有可能是两盒米饭$00$或者两盒青菜$11$。

那么这个时候，我们就不得不拆掉一个寿司。

请写一个程序，求要拆掉多少个寿司。
### 思路：
我们可以逆着推导。

既然题目要求拆掉多少个寿司，我们就可以求有多少个寿司可以保留。

这个非常好求，一遍循环可以搞定。

然后用$n$减去保留寿司个数即可。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long q=0,w=1;
	char ch=getchar();
	while(ch>'9' || ch<'0'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')q=q*10+ch-'0',ch=getchar();
	return q*w;
} //快读 
void write(long long out){
	if(out<0){puts("-");out=abs(out);}
	if(out>9)write(out/10);
	cout<<out%10;
} //快写 
char input_last,input_now; //记录上一个字符和这一个字符 
long long n,i,j,cnt;
int main(){
	n=read(),cnt=n;
	for(i=1;i<=2*n;i++){
		input_now=getchar(); //输入字符 
		if(input_now!=input_last && i!=1){ //注意：i=1时 input_now!=input_last但不符合题意 
			cnt--,i++;
			input_now=getchar();
			/* 如果 上一个字符和这一个字符 不相等
			   那么下一个字符就可以不参与比较
			   故此 i++且 输入input_now */
		}
		input_last=input_now; // 替换上一个字符
	}
	getchar(); //换行 
	write(cnt),cout<<endl; //输出 
	return 0; //完美收场 
}
```
### 注：
这是一道被恶意评分的题目，实际是一道水题！

---

## 作者：Federico2903 (赞：1)

# 贪心  
## 思路
尽量不拆，但是如果遇到相邻两个一样的就必须得拆。  
这题只需要算这个塔哪几个可以不拆开，用总数减去不拆的数量即可。  
坑点：如果有一个寿司判定为可以不拆开，那么字符串遍历的位置应该加二！相当于跳过下一个物品（视作整体），避免出现粘着的寿司重复计算。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int main(){
	int n;
	cin >> n >> s;
	int sum=n;
	for(int i=0;i<n*2-1;i++){
		if(s[i]!=s[i + 1]){
			sum--;//不用拆 
			i++;//找到了必须跳过下一个物品 
		}
	}
	cout << sum << endl;//输出 
}
```

---

## 作者：ljqqq123✅ (赞：1)

**直接上代码，注释在代码里**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,one,zero;//one代表菜，zero代表米饭
char a[605];//字符串
int main(){
	cin>>n>>a;
	for(int i=0;i<2*n-1;i++){//把所有菜和米饭的个数求出来
		if(a[i]=='0')one++;
		else zero++;
	}
	for(int i=0;i<2*n-1;i++){
		if(a[i]!=a[i+1]){//因为一个寿司里是一个菜和一个饭，所以如果有两个相邻的话，就不用再拆开
			i++;//下一个就不用判断了
			one--,zero--;//不用拆开，one和zero都-1
		}
	}
	cout<<max(one,zero)<<endl;//要拆开的个数肯定是one和zero最大的那个，至于为什么自己想
	return 0; 
}
```

---

## 作者：谷民 (赞：1)

### 题解 AT1578 【寿司タワー】

本题题意不太清晰，通俗地讲是求字符串a中非子串“01”“10”个数的二分之一（由于题目定义寿司是由两个字符构成，这也是坑点，字符串大小需开n的二倍）

思路：通过每一个字符和下一个字符，如果不同则可以凑成一个寿司，再用总数减凑成寿司数

```
#include<bits/stdc++.h>
using namespace std;
int n,res;
char a[605];//要开n二倍
int main(){
	cin>>n>>a;
	for(int i=0;i<2*n-1;i++){//枚举，注意范围，不能超出字符串最后一位
		if(a[i]!=a[i+1]){//若可以构成寿司就计数并跳过这个寿司
			i++;
			res++;
		}
	}
	cout<<n-res<<endl;//求拆的寿司，减去后输出
	return 0; 
}
```


---

## 作者：_Hero_ (赞：0)

# 分析
题目要用寿司做寿司塔，但是可能给出的食物不是寿司，而是两个米饭或两个青菜，这时你就不得不拆开。我们可以先求有几个米饭和青菜，再求有几个寿司不用拆开，也就是两个相邻的数不同，建议使用字符串来解决。如果找到了一个寿司，要跳过下一个字符避免重复判断，可以用一个变量做标记，每回都清零，因为一个寿司有一个米饭一个青菜，还要把米饭和青菜的个数都减一。再看要拆开的米饭多还是青菜多，最后输出多的那个数。

# 代码
```
#include<bits/stdc++.h>
using namespace std;
int r,v,n,x;
string s;
int main(){
	cin>>n>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]==0)r++;//求出青菜和米饭的个数
		else v++;
	}
	for(int i=0;i<2*n-1;i++)//N个寿司，每个寿司两个字符，坐标从0开始，所以是2*n-1
	{
	if(x==0)//是否判断
	{
		if(s[i]!=s[i+1])
		{
		x=1;//标记
		r--;
		v--;	
		}
	}
	else
	{
		x=0;
	}
	}
	if(r>v)//输出多的个数
	cout<<r<<endl;
	else
	cout<<v<<endl;
	return 0;
}
```


---

## 作者：EthanC_ (赞：0)

### 思路：
遍历一遍字符串，看看里面长度为 $ 2 $ 的 $ 01 $ 串的个数，如果有一个 $ 01 $ 串就将寿司个数 $ n $ 减去 $ 1 $，最后输出 $ n $。
### 代码：
```cpp
#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    string s;
    cin>>s;
    for(int i=0;i<s.size();++i){//遍历字符串，寻找有多少个01串
        if(s[i]=='0'&&s[i+1]=='1'||s[i]=='1'&&s[i+1]=='0'){
            n--;//找到可以拿走的总数就减一，n就是剩下的数量
            i++;
        }
    }
    cout<<n<<endl;//输出剩下的数量（记得换行）
    return 0;//完结撒花^_^
}
```


---

## 作者：Fire_Raku (赞：0)

### 题目分析：

题意：有 $n$ 个寿司，有一个饭和一片菜组成，要用这些寿司筑成寿司塔（字符串 $s$），寿司可以直接放，翻转和拆开，问你最少拆开几个，才能做出说给的寿司塔。

这题是道水题，把思路缕清晰了就行了，首先，我们要尽可能地少拆开寿司，我们就可以算这个寿司塔，有几个可以不拆开，然后在用总数减去能不拆开的寿司的数量，就是我们想要的答案了。

这么讲可能有点太概括了点，如果听不懂，我们看一下样例 $1$：

```cpp
3
101100
```

有三个寿司，要弄成 $101100$ 这样的寿司塔，我们就从头开始循环枚举字符，如果这个字符与它后面的字符是 $10$，或 $01$，这两个显然就不需要拆开，为什么 $01$ 也可以呢？因为寿司是可以翻转的，$01$ 不就是翻转 $10$ 翻转一下？所以，枚举完一遍以后，我们再把总数减去不用翻转的数量，就结束了。

**蒟蒻的代码：**

```cpp
#include<bits/stdc++.h>
using namespace std ;
int ans , n ; 
string s ;
int main(){
	cin >> n ; 
	cin >> s ;
	for(int i = 0 ; i < s.length() ; i++){
		if((s[i] == '1' && s[i + 1] == '0') || (s[i] == '0' && s[i + 1] == '1')){ //判断条件
			i++ ; //i++是因为这边加1，循环结束了也加1，就等于加了2，这样做就不会算到重复的黏到一起的寿司了
			ans++ ; 
		}
	}
	cout << n - ans << endl ; //总数减不用拆的寿司
	return 0 ; 
}
```

Tips：这篇题解看了一下，和一楼挺像的，我的话感觉......感觉！能更通俗易懂一点，求过qwq

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT1578)

小学生又双叒叕来写题解啦！

个人认为这题就考你的理解能力，因此，得先把题读懂。

寿司就是  _01_ 或 _10_ 字符的组合，减少拆开寿司的次数，本质上就是**保留完整的寿司**。

因此，只需去枚举目标寿司塔中完整寿司的个数即可。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
	int n, cnt = 0;
	string s;
	scanf("%d", &n);
	cin >> s;
	int len = 2*n;
	for (int i = 1; i < len; i++)  //注意要从一开始。 
		if (s[i] != s[i-1])  //此时是一个完整的寿司，不用拆开。 
		{
			cnt++;
			i++;
		}
	printf("%d\n", n - cnt);  //记得按要求换行。 
	return 0;
}
```


---

## 作者：Node_Edge (赞：0)

**题意化简：**

有长度 $2n$ 的 $01$ 字符串。

如果其中相邻两个字符相同时，那么拆开这个字符串，求解开寿司的个数。

**思路：**

相邻的两个相同字符是要拆开。

**代码：**

```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt,n;
int main(){
	string s;
	scanf("%d", &n);
	cin >> s;
	for (int i = 1; i <2*n; i++){
		if (s[i] != s[i-1]){//判断相邻
			cnt++;
			i++;
		}
    }
	cout<<n-cnt<<endl;//岛国题要换行
	return 0;
}
```


---

