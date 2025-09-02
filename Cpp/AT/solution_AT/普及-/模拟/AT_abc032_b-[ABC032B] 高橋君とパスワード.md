# [ABC032B] 高橋君とパスワード

## 题目描述

高桥君的公司里有一个秘密的金库。由于这个金库需要密码才能进入，而高桥君已经忘记了这个密码。但是幸运的是，他的手边有这个密码的提示，提示是以下这样写的。


- 密码为这张纸上写着的字符串s的长为k的某个子串。

高桥君只需试完所有可能的密码就能打开金库，他因此很高兴~但是，字符串s非常长因此密码的可能情况有很多种。很明显，重复的密码没有必要再试一遍。所有在亲自将所有密码试一遍之前，需要数出有多少种不同的密码。

你的任务就是将给定的字符串s中需要试的相异密码的个数告诉高桥君。

字符串s的“子串”指，字符串s里所含的一段区间的字符取出所得字符串。例如：$abc$的子串有：$a$,$b$,$c$,$ab$,$bc$,$abc$。而请注意，像$ac$或$ba$这样的字符串并非$abc$的子串。

## 样例 #1

### 输入

```
abcabc
2```

### 输出

```
3```

## 样例 #2

### 输入

```
aaaaa
1```

### 输出

```
1```

## 样例 #3

### 输入

```
hello
10```

### 输出

```
0```

# 题解

## 作者：三氯甲硅烷 (赞：1)



------------
~~这真的是紫题吗？？？~~

其实很简单的一道题

主要介绍substr和set的用法


先贴代码：

```cpp
#include<iostream>
#include<string>
#include<set>
using namespace std;
string s;
int k;
int main() {
    cin>>s>>k;
    int l = s.length();
    if(l<k) {
    	cout<<0<<endl;
        return 0;
    }
	set<string> a;
    for(int i=0;i<=l-k;i++) {
        a.insert(s.substr(i,k));
    }
    cout<<a.size()<<endl;
    return 0;
}
```

set是一个集合，内部使用的是红黑树，速度不错；
s.substr(a,b)可以从已知的字符串s中从第a个截取b个字符。（下标从零开始）

---

## 作者：Egg_eating_master (赞：0)

~~？？？紫题？？？~~

楼下用set我用map~

map其实就是数组，只不过下标的类型可以不为int~

定义格式：
```
map<类型一，类型二>mp;
```
相当与定义了一个下标类型为类型一，其值为类型二的mp数组。

好啦，可以上代码了~
```
#include<bits/stdc++.h>
using namespace std;
string s;
map<string,bool>mp;
//相当于定义了一个下标类型为string的bool数组 
int k;
int ans;
int main(){
	cin>>s>>k;
	if(s.size()<k){//如果要的字符串长度都大于原字符串
		cout<<0<<endl;//那么一定不存在
		return 0;
	}//注意这里必须加一个特判，否则会RE三个点
	for(int i=0;i<=s.size()-k;i++){
		if(!mp[s.substr(i,k)])ans++;//没出现过，则答案加一
		mp[s.substr(i,k)]=1;//把此字符串标为出现过
	}
	cout<<ans<<endl;//输出答案
	return 0;
}
```

---

## 作者：monstersqwq (赞：0)

#### 题目大意：

求一个字符串 $s$ 中 $k$ 长度的不同子串个数。

因为此题数据较小，可以不用 set 或者 map，直接记录所有的子串，出现新的时候与前面的子串比较一下即可。

一定要时刻牢记，string 类型的下标是从0开始的，作者被坑了好几次。

还有，枚举子串时注意不要越界，具体可看代码理解。

AT 题中不换行，听取 WA 声一片。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
string s,ans[305];
int cur,k;//cur记录当前有多少不同的子串，方便对比和输出答案
int main()
{
    cin>>s>>k;
    int tmp=s.length();
    if(tmp<k)
    {
    	cout<<"0"<<endl;
    	return 0;
	}//特判无子串的情况，不然会越界（其实也不会，不过这样方便理解）
	for(int i=0;i<=tmp-k;i++)
	{
		string tmps=s.substr(i,k);//substr的用法楼下几位大佬都介绍了
		bool flag=false;
		for(int j=1;j<=cur;j++)
		{
			if(ans[j]==tmps) flag=true;
		}
		if(flag==false)
		{
			cur++;
			ans[cur]=tmps;
		}
	}
	cout<<cur<<endl;
    return 0;
}
```


---

## 作者：谷民 (赞：0)

### 题解 AT1742 【高橋君とパスワード】

**题意**：在$s$中长度为k的不同的子串有多少个

因此，就有了一个直观的思路，暴力枚举每一个长为$k$的子串，若没访问过标记访问，答案增加。我们用$map$来充当标记是否访问的$vis$数组，其特点是下标可以为字符串，剩下与数组相同。最后输出所统计的答案即可，**注意AT题库输出需要换行**。

**代码**：


```
#include<bits/stdc++.h>
using namespace std;
map<string,bool>vis; \\map的定义
string s;
int n,ans;
int main(){
	cin>>s>>n;\\读入
	int l=s.length();\\长度
	if(l<n){
		printf("0\n");
		return 0;
	}
	for(int i=0;i<=l-n;i++){\\枚举字符串第一个字符
		if(!vis[s.substr(i,n)]){\\用substr求以i起始长为n的子串
			ans++;//没访问过累加答案，标记
			vis[s.substr(i,n)]=1;
		}
	}
	printf("%d\n",ans);//输出换行，不换行会WA
	return 0;
}

```


---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

这道题其实就是求字符串s中有多少个不重复的长度为k的子串。知道了题目要我们求什么之后，敲代码就很容易了。我们从下标0开始，枚举每一个长度为k的子串，将它与前面的子串比较一下是否重复，如果没有重复，我们就将它存起来。

这道题本蒟蒻被坑了一下，就是当字符串s长度小于k时，我们要直接输出0并退出程序，不然就会像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/v9dgul2x.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

好了，以上就是思路，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
string st,st1[1010];
int ans,k,pd;
int main()
{
    cin>>st>>k;
    if(st.size()<k)//判断字符串s长度是否小于k时
    {
    	cout<<0<<endl;
    	return 0;
    }
	for(int i=0; i<=st.size()-k; i++)
	{
		string st2=st.substr(i,k);//截取
		pd=1;
		for(int j=1; j<=ans; j++)
		{
			if(st1[j]==st2)//看看是否重复
			{
				pd=0;
				break;
			}
		}
		if(pd==1)ans++,st1[ans]=st2;//如果没有重复
	}
    cout<<ans<<endl;//记得换行
    return 0;
}
```


好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

