# Vicious Keyboard

## 题目描述

题目背景

Tonio 有一个只有“V,K”两个键的键盘。


一天，她打出了一个只有这两个字符的字符串。当这个字符串里含有"VK"这个字符串的时候，honoka 就特别喜欢这个字符串。所以，她想改变至多一个字符（或者不做任何改变）来最大化这个字符串内"VK"出现的次数。给出原来的字符串，请计算她最多能使这个字符串内出现多少次"VK"。(只有当"V"和"K"正好相邻时，我们认为出现了"VK"。)

## 样例 #1

### 输入

```
VK
```

### 输出

```
1
```

## 样例 #2

### 输入

```
VV
```

### 输出

```
1
```

## 样例 #3

### 输入

```
V
```

### 输出

```
0
```

## 样例 #4

### 输入

```
VKKKKKKKKKVVVVVVVVVK
```

### 输出

```
3
```

## 样例 #5

### 输入

```
KVKV
```

### 输出

```
1
```

# 题解

## 作者：世末OIer (赞：2)

太水了，只有入门难度吧

枚举时哪一个V改成K或者哪一个K改成V

```cpp
#include<bits/stdc++.h>
#define mp make_pair
#define fs first
#define se second
#define memset(a) memset(a,0,sizeof(a))
using namespace std;
string s;
inline int sum(){
	int i,re=0;
	for(i=0;i<s.size()-1;i++){
		if(s.substr(i,2)=="VK") re++;
	}
	return re;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin>>s;
	int i,mx=-135;
	mx=max(mx,sum());
	for(i=0;i<s.size();i++){
		if(s[i]=='V'){            //V改K
			s[i]='K';
			mx=max(mx,sum());
			s[i]='V';
		}else{                    //K改V
			s[i]='V';
			mx=max(mx,sum());
			s[i]='K';
		}
	}
	cout<<mx<<endl;
	return 0;
}
```

---

## 作者：TLMPEX (赞：1)

枚举每一个字母，如果是```K```则变成```V```否则变成```K```了，然后求出有多少个```VK```了，取最大值。


·字母变化后要还原。

·最大值包括什么都不变的情况。

代码如下。
```c
#include<bits/stdc++.h>
using namespace std;
string k;
int main(){
	int l,i,j,z=0;
	cin>>k;
	l=k.size();
	for(i=0;i<l-1;i++)
		if(k[i]=='V'&&k[i+1]=='K')z++;//求什么都不变有多少个VK
	for(i=0;i<l;i++){//枚举每一个字母
		if(k[i]=='V')k[i]='K';//如果是V则变K
		else k[i]='V';否则变V
		int x=0;
		for(j=0;j<l-1;j++)
			if(k[j]=='V'&&k[j+1]=='K')x++;//求变后有多少个VK
		z=max(z,x);//取最大值
		if(k[i]=='V')k[i]='K';
		else k[i]='V';
		//变回原来的
	}
	cout<<z;
}
```


---

## 作者：xzllll07 (赞：0)

字符串的长度 $\le$ 100，所以可以直接暴力求解。

具体的方法也很简单，先用变量 $ans$ 记录原字符串 VK 的数量。

之后将一个字符改为另一个，遍历字符串，计算有多少个 VK，将变化后字符串中 VK 的个数与 $ans$ 比较，如果比 $ans$ 多，就用变化后字符串 VK 的数量代替 $ans$ 原来的值。

对每个字符重复以上操作即可，最终的 $ans$ 的值就是 VK 最多出现的次数。

时间复杂度 $O(n^2)$，数据范围较小，所以不会超时。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int ans;
string s;

int main()
{
    cin>>s;
    int len=s.length();
    for (int i=0;i<len-1;i++)
    {
        if (s[i]=='V' && s[i+1]=='K')
        {
            ans++; //记录初始 VK 的个数
        }
    }
    for (int i=0;i<len;i++)
    {
        if (s[i]=='V') 
        {
            s[i]='K'; // V 改为 K
            int tmpans=0; //记录变化后 VK 个数
            for (int j=0;j<=len-2;j++) //循环到 len-2 是因为要调用 s[j] 和 s[j+1] 如果遍历到 len-1 会越界
            {
                if (s[j]=='V' && s[j+1]=='K')
                {
                    tmpans++;
                }
            }
            ans=max(ans,tmpans); //如果出现了更多的 VK，就代替原来的 ans
            s[i]='V'; //记得要把字符改回来
        }
        else if (s[i]=='K')
        {
            s[i]='V';// K 改为 V
            int tmpans=0;//同上，遍历字符串计算 VK 个数
            for (int j=0;j<=len-2;j++) 
            {
                if (s[j]=='V' && s[j+1]=='K')
                {
                    tmpans++;
                }
            }
            ans=max(ans,tmpans);
            s[i]='K';
        }
    }
    cout<<ans;
   
} 
```


---

## 作者：LRL65 (赞：0)

由于这题的数据范围是n<=100,所以直接o($a^2$)暴力就行了.但是需要注意的是这题**细节很多**.

暴力其实就是将每一个字母都换成另一个字母,然后求和比大小.需要注意的细节是:

- 一开始需要先算一下原字符串中vk的数量,因为可以不变.
- 累加器记住清零(这个没啥难的,提醒一下)
- 每个字母换完以后还要变回来

上代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int ans=0;
int main() {
	cin>>s;
    for(int i=1;i<s.size();i++) if(s[i-1]=='V'&&s[i]=='K')ans++;//一开始算一次
	for(int i=0;i<s.size();i++){
		if(s[i]=='K')s[i]='V';
		else s[i]='K';
		int k=0;
		for(int i=1;i<s.size();i++) if(s[i-1]=='V'&&s[i]=='K')k++;
		ans=max(k,ans);
		if(s[i]=='K')s[i]='V';//要变回来
		else s[i]='K';
	}
	cout<<ans<<endl;
}
```


---

## 作者：q_sum (赞：0)

蒟蒻又来写题解了。

这道题考察的是字符串，解法不难，数据量很小，暴力枚举即可，首先第一重循环枚举要改变的字符，第二重枚举改动后的字符串中有几个连续的“$VK$”,注意还要枚举一遍原串，不然在“$VKVKVKVKVK……$”这样的数据里会出错。

代码：

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
string s;
int mx,len;//mx用来储存最大值，len用来储存原串长度
int main()
{
	cin>>s;//输入
	len=s.length();//求原串长度
	for (int i=1;i<len;i++)
		if(s[i-1]=='V'&&s[i]=='K')
		    mx++;//求原串答案
	for (int i=0;i<len;i++)
	{
		string ss=s;int cnt=0;//创建新串，将计数器清零
		if(ss[i]=='V')
		  ss[i]='K';else
		  ss[i]='V';//修改新串字符
		for (int i=1;i<len;i++)
		   if(ss[i-1]=='V'&&ss[i]=='K')
		     cnt++;//求新串答案
		mx=max(mx,cnt);//统计最大值
	}
	cout<<mx<<endl;//输出
	return 0;
}
```

[评测记录](https://www.luogu.com.cn/record/39862020)


---

