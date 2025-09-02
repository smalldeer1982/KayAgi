# NAJPF - Pattern Find

## 题目描述

### 题意：

给出两个字符串 $A,B$ ，求 $B$ 在 $A$ 中所有出现的次数和每一次出现的位置。假如没有出现输出`Not Found`。

# 题解

## 作者：coldy_rainy (赞：2)

**前言**

[SP原题链接](https://www.spoj.com/problems/NAJPF/)

[洛谷题目链接](https://www.luogu.com.cn/problem/SP21524)

[AC记录](https://www.luogu.com.cn/record/100060520)

**题目大意**

给出两个字符串 $A,B$，求 $B$ 在 $A$ 中出现的次数以及每次出现的位置，若不存在输出 `Not Found`.

**分析**

就是一个查找字串的模板，蒟蒻还没学 KMP 查找字串算法，就只用最朴素的暴力求解法吧。

我们可以在因为要查找 $A$ 中与 $B$ 相同的子串，所以子串的首字母肯定等于 $B$ 的首字母。因此，可以考虑枚举 $A$ 的每个字母，若与 $B$ 的首字母相同，就向后查看后面的字符是否能与 $B$ 对的上。能就将次数加一，并存储到数组即可，否则输出 `Not Found` 结束。

需要注意的是，题目要求输出时每组数据间要有一个空行，因此输出时要加两个换行符。如果 $A$ 的长度还没 $B$ 大，则 $A$ 中肯定不含 $B$ 子串，直接输出 `Not Found` 结束。

由于 $A,B$ 的长度可达 $10^6$，所以相应的存储答案数组也要开到这么大。

**代码**

```cpp
#include<bits/stdc++.h>
#define maxn 10000005//最大数组长度
using namespace std;
int n,all[maxn]/*存储答案数组*/,cnt/*次数*/;
string a,b;
int main()
{
   cin>>n;
   while(n--)
   {
    memset(all,0,sizeof(all));/*清空数组*/
    cnt=0;/*清空次数*/
    cin>>a>>b;
    if(a.size()<b.size())//如果B长度大于A，直接输出Not Found并退出
    {
        cout<<"Not Found\n\n";
        continue;
    }
    for(int i=0;i<a.size();i++)//枚举每个字符
    {
      if(a[i]==b[0])//与首字母相同
      {
        for(int j=0;j<b.size();j++)if(a[i+j]!=b[j])goto END;//若后面的字符与B对不上，使用标签退出本次判断
        all[++cnt]=i+1;//到这里的肯定是答案，将次数加一，存储（注意题目中的字符串从1开始，所以要加一）
      }
      END:
      continue;//标签与括号间要加一个语句
    }
    if(cnt==0)//如果没答案
    {
        cout<<"Not Found\n\n";
        continue;
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)cout<<all[i]<<' ';//顺序输出答案
    cout<<"\n\n";
   }
   return 0;
}
```
**后记**

抄代码是不好的习惯哦。

耗时 240 ms。



---

## 作者：_H17_ (赞：1)

## 题目大意

输入两个字符串 $A,B$，求 $B$ 在 $A$ 中出现了几次。

## 题目分析

以下表示 $\lvert x \rvert$ 为字符串 $x$ 的长度。

如果 $\lvert B \rvert > \lvert A \rvert$ 那肯定不行。

否则遍历一下 $A$，对于每一次判断 $A_{i+j}=B_j(1\le j\le\lvert B\rvert,1\le i+j \le \lvert A\rvert)$ 是否成立，不成立结束循环（循环指循环 $j$ 的那一层），否则让 $ans \gets ans +1,a_{ans}=i$（即更新答案数和答案位置）。

**注意：要输出俩换行（在测试数据之间）。**

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,lst[1000001];//lst存位置
string a,b;
void Main(){
    memset(lst,0,sizeof(lst));
    ans=0;
    cin>>a>>b;
    if(a.size()<b.size()){
        cout<<"Not Found\n\n";
        goto gt;
    }//不行
    for(int i=0,f;i<a.size();i++){
        f=1;
        for(int j=0;j<b.size();j++){
            if(a[i+j]!=b[j]){
                f=0;
                break;//不同
            }
        }
        if(f)
            lst[++ans]=i+1;//加进数组
        else
            continue;
    }
    if(!ans){
        cout<<"Not Found\n\n";
        goto gt;
    }//失败了
    cout<<ans<<'\n';
    for(int i=1;i<=ans;i++)
        cout<<lst[i]<<' ';
    cout<<"\n\n";//别忘了换行
    gt:
    return;
}
int main(){
    int _;
    for(cin>>_;_;--_)//多组数据
        Main();
    return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

## [SPOJ 原题](https://www.spoj.com/problems/NAJPF/)
## [luogu 原题](https://www.luogu.com.cn/problem/SP21524)

# 题目大意
共有 $T$ 组数据，每组数据输入一行，其中包含两个字符串 $a$，$b$。求 $b$  在 $a$ 中出现的次数和每一次出现的位置。

如果 $b$ 在 $a$ 中没有出现，就输出 `Not Found`。

Tip：在两次输出中间，要空一行。~~被这个东西卡了好久~~

# 题目思路

其实接近 `KMP` 算法模板，但本蒟蒻还没学会 `KMP`，就直接暴力了。

小小的优化：因为要查找 $a$ 中与 $b$ 相同的子串，所以子串的首字母肯定就是 $b$ 的首字母。枚举 $a$ 的每个字母，若与 $b$ 的首字母相同，就向后查看后面的字符是否能与 $b$ 对的上。当然用 `compare` 函数就不需要这个优化。

# 参考代码

```cpp
#include<bits/stdc++.h>
const int MAXN=1e6+5;
using namespace std;
int cnt;
int ans[MAXN];
string a,b;
void init(){cout<<"Not Found\n\n";}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        memset(ans,0,sizeof ans);
        cnt=0;
        cin>>a>>b;
        if(a.size()<b.size()){
            init();
            continue;
        }
        for(int i=0;i<a.size();i++){
            bool flag=0;
            if(a[i]==b[0]){
                for(int j=0;j<b.size();j++)
                    if(a[i+j]!=b[j])
                        flag=1;
                if(!flag)
                    ans[++cnt]=i+1;
            }
            if(flag)
                continue;
        }
        if(!cnt){
            init();
            continue;
        }
        cout<<cnt<<endl;
        for(int i=1;i<=cnt;i++)
            cout<<ans[i]<<' ';
        cout<<"\n\n";
    }
}
```

---

## 作者：e4fsrc2e4fsrc2 (赞：0)

## [NAJPF - Pattern Find](https://www.luogu.com.cn/problem/SP21524)

## 思路分析
蒟蒻不会 KMP 算法，就只能用 $\verb|string|$ 库中的 $\verb|compare|$ 函数（不会点[这里](https://blog.csdn.net/qq_40968179/article/details/104384232))。

设 $|s|$ 表示字符串 $s$ 的长度。

1.判断字符串 $A$ 的长度是否大于等于 $B$ 的长度：若是，进入下一步；若不是，输出 $\texttt{Not Found}$。

2.用 $\verb|compare|$ 函数判断字符串 $A$ 的第 $i$ 位到第 $i+|b|-1$ 位所组成的字符串与字符串 $B$ 是否相等（代码中 $\verb|a.compare(i,lb,b)|=0$ 就是相等的意思），相等就用数组记录下来。

PS：有多组数据，要记得清空数组和所记录的个数 $\verb|cnt|$。
## AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define R register int
using namespace std;
const int N=1e6+1;
int t,cnt,la,lb,x[N];
string a,b;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a>>b;cnt=0;
		la=a.size(),lb=b.size();
		if(la<lb){cout<<"Not Found\n\n";continue;}
		for(R i=0; i<=la-lb; i++)
			if(!a.compare(i,lb,b))
				x[++cnt]=i+1;
		if(cnt){
			cout<<cnt<<'\n';
			for(R i=1; i<=cnt; i++)cout<<x[i]<<' ';
			cout<<"\n\n";
		}else cout<<"Not Found\n\n";
	}
	return 0;
}
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/SP21524)

[SPOJ 链接](https://www.spoj.com/problems/NAJPF/)

题目大意：

一共有 $T$ 组数据。每组数据输入两个字符串 $A$ 和 $B$，找出所有与字符串 $B$ 相等的 $A$ 的子串，并输出其个数和首字母下标。如果没有，输出 $\texttt{Not Found}$。

思路：

暴力枚举子串。每次对比每一个字符，如果不相等退出，否则计数器加 $1$。

坑点：

1. 每个数据之间有一个空行！
1. 需要特判 $A$ 的长度是否小于 $B$ 的长度，否则会 RE！

上代码：
```cpp
#include <iostream>
using namespace std;

int ans[1000001];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout加速
    int t;
    cin >> t;
    while (t--){
        string a, b;
        cin >> a >> b;
        // 防 RE 特判！！！
        if (a.size() < b.size()){
            cout << "Not Found\n\n";// 坑人格式：两个换行
        } else {
            int cnt = 0;
            // 枚举子串起点
            for (int i = 0; i <= a.size() - b.size(); i++){
                if (a[i] == b[0]){// 如果起点的位置相同
                    // 那么就判断所有的
                    bool err = false;
                    for (int j = 0; j < b.size(); j++){
                        if (a[i + j] != b[j]){
                            err = true;
                            break;
                        }
                    }
                    if (!err){// 如果没有错
                        ans[++cnt] = i + 1;// 那么就把情况压到数组里
                    }
                }
            }
            if (cnt == 0){// 如果没有
                cout << "Not Found\n\n";// 坑人格式：两个换行
            } else {
                cout << cnt << "\n";
                for (int i = 1; i <= cnt; i++){
                    cout << ans[i] << " ";
                }
                cout << "\n\n";// 坑人格式：两个换行
            }
        }
    }
    return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/SP21524)     
KMP 板子题。    
寻找子串，明显是 KMP。   
这里先简单讲一讲 KMP 算法：    
这个算法会在程序开始时计算出一个 next 数组，$next_i$ 表示子串前 $i$ 项的最长前后缀（不能是这 $i$ 项本身）长度，比如 `abab` 的 $next_4$ 为 $2$。    
比较的时候我们将暴力算法改良，如果在子串第 $i$ 位出现了不匹配的情况，我们可以跳过 $next_i$ 个字符。如果匹配成功就记录位置。       
CODE：   
```
#include <iostream>
#include <string>
using namespace std;
int t,lena,lenb,nxt[1000001],n,a[1000001];
string s1,s2;
void getnext(){//生成next数组
	int j=0;
	for(int i=1;i<lenb;i++){
		if(s2[i]==s1[j]){//可以继续扩展就继续扩展
			nxt[i]=nxt[j++]+1;
		}else{
			nxt[i]=nxt[j-1];//不能扩展就找一个较短的
			j=nxt[j-1];
		}
	}
}
void KMP(){//KMP主体
	for(int i=0;i<lena;i++){
		for(int j=0,k=i;j<lenb;j++,k++){//暴力寻找
			if(s1[k]!=s2[j]){//不匹配就跳过next[j]个字符
				i+=nxt[j];
				break;
			}
			if(j+1==lenb){//匹配成功，继续记录答案
				a[n++]=i+1;
				break;
			}
		}
	}
}
int main(void){
	cin>>t;
	while(t--){
		n=0;//多测要清空
		cin>>s1>>s2;
		lena=s1.length();
		lenb=s2.length();
		getnext();
		KMP();
		if(!n){//没找到
			printf("Not Found\n");
		}else{
			printf("%d\n",n);//找到了就输出
			for(int i=0;i<n;i++){
				printf("%d ",a[i]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
```


---

## 作者：TheCliffSwallow (赞：0)

[原题链接](https://www.spoj.com/problems/NAJPF/)

建议降橙。
### 题意简述
判断字符串 $A$ 是否有子串 $B$。
### 思路

先判断 $A$ 是否比 $B$ 短，如果比 $B$ 短则肯定不行，再枚举 $A$ 的每个字符，如果有个字符与 $B$ 的开头字符相等，那么在 $A$ 的这个字符后枚举 $B$ 的长度，判断是否与字符串 $B$ 相等，如果不相等就跳出循环，否则用一个数组记录其位置，用一个布尔型变量记录是否相等，最后判断这个变量是否为真并输出。

### AC CODE
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#define int long long
using namespace std;
int t,j,k,alen,blen,n[1000005];//n数组记录每次出现的位置
bool f;
string a,b;
signed main(){
	std::ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		cin>>a>>b;
		alen=a.size(),blen=b.size();
		if(alen-blen>=0){//如果A比B短则肯定不行
			for(int i=0;i<=alen-blen;i++){//枚举A的每个字符
				if(a[i]==b[0]){//如果这个字符等于B的开头字符时
					for(j=0;j<blen;j++){
						if(b[j]!=a[i+j])	break;//如果后面的字符串有个字符不同，则跳出循环
					}
					if(j==blen){//如果之前没有跳出循环，则j肯定等于blen
						k++;
						n[k]=i+1;//注意位置是下标加一
						f=true;
					}
				}
			}
			if(f==false){
				cout<<"Not Found\n";//没有子串B
			}else{
				f=false;
				cout<<k<<endl;
				for(int i=1;i<=k;i++)	cout<<n[i]<<" ";//输出每次的出现位置
				cout<<endl;
			}
			k=0;
			cout<<endl;//别忘每组数据要两个换行
		}else{
			cout<<"Not Found\n\n";//A比B短
		}
	}
	return 0;
}
```

同时要注意，$s.size()$ 函数返回值为无符号整形数，如果将代码中的所有 `alen`，`blen` 代替为 `a.size()`，`b.size()`，会 RE，所以在将它与数加减比较的时候，最好先将它转换为 `int` 在进行加减比较。

---

## 作者：ztntonny (赞：0)

## 题意
其实还挺好理解的，就是输入几组字符串，在前一个中搜索后一个的出现次数和位置，有则都分别输出数量和位置，如果没有则输出 ```Not Found```。
## 思路
最先的剪枝：如果字符串 $a$ 比 $b$ 短，就没有。否则首先枚举字符串 $b$ 第一位在前字符串 $a$ 中出现的位置，不是直接跳过，是的话往后挨个判断是否一样，如果有不一样直接结束并且标记，如果一直一样就存入位置的数组，最后一并输出，并且记录个数。最后如果个数大于 $0$ 就输出个数与位置，否则输出 ```Not Found```。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    string a , b;
    int c;
    cin >> c;
    while ( c-- )
    {
        cin >> a >> b;
        int lena = a.size() , lenb = b.size() , position[1000005] , k = 0;
        if ( lena < lenb )//第一个剪枝
            cout << "Not Found\n\n";
        else
        {
            for ( int i = 0; i <= lena - lenb; i++ )
            {
                bool ifs = 1;
                for ( int h = i; h < lenb + i; h++ )//找头
                {
                    if ( a[h] != b[h - i] )//如果不一样
                    {
                        ifs = 0;//标记
                        break;
                    }
                }
                if ( ifs == 1 )//如果一直没标记即一直一样
                {
                    position[k] = i + 1;//存入数组
                    k++;//计数器加一
                }
            }
            if ( k == 0 )//如果没有
                cout << "Not Found\n\n";
            else
            {
                cout << k << endl;//个数
                for ( int j = 0; j < k; j++ )
                    cout << position[j] << " ";//位置
                cout << endl;
            }
        }
    }
    return 0;
}
```

---

## 作者：m1kusama (赞：0)

### 题目大意
给两个字符串 $a$ 、$b$ ，求 $b$ 在 $a$ 中是否出现，出现几次，位置在哪里。
### 分析
字符串匹配问题，还要求统计数量和位置，标准的KMP。~~虽然暴力能过~~
### 代码
具体讲解看注释。**因为此题不是模板，所以对KMP算法的详细讲解较少**，如果初学KMP，请移步[P3375](https://www.luogu.com.cn/problem/P3375)。
```cpp
#include<bits/stdc++.h>//杜绝抄袭！
using namespace std;
int n,k,len1,len2,t,ans,ans1[1000005];
int next1[1000005];
char s1[1000005],s2[1000005];

void next_(){ //求最长公共前后缀。
	int t1=0,t2=-1;
	next1[0]=-1;
	while(t1<len2){
		if(t2==-1||s2[t1]==s2[t2]) next1[++t1]=++t2;
		else t2=next1[t2];
	}
}

void KMP(){//KMP核心。
	int t1=0,t2=0;
    while(t1<len1) //当还没有匹配完毕，就往后循环。
    { 
        if(t2==-1 || s1[t1]==s2[t2]) //如果相同就++。
            t1++,t2++;
        else t2=next1[t2]; //不同就要发挥next数组的作用了，直接跳到next[t2],时间复杂度更优。
        if(t2==len2) ans1[ans]=t1-len2+1,t2=next1[t2],ans++;//全部匹配上就记录位置，数量++。
    }
}

int main(){
	cin>>t;
	for(int i=0;i<t;i++){
		ans=0;
		memset(ans1,0,sizeof(ans1));//因为多组数据，先初始化数组。
		cin>>s1>>s2;
		len1=strlen(s1);
		len2=strlen(s2);
		next_();
		KMP();
		if(ans==0){ //下面是输出
			cout<<"Not Found"<<endl<<endl;
		}else{
			cout<<ans<<endl;
			for(int j=0;j<ans;j++){
				cout<<ans1[j]<<" ";
			}
			cout<<endl<<endl;
		}
	}
	return 0;
} 
```
有问题请在评论中指出，谢谢各位大佬！

---

