# Permute Digits

## 题目描述

给出两个正整数a,b。在十进制下重排a，构造一个不超过b的最大数，不能有前导零。允许不去重排a。

## 样例 #1

### 输入

```
123
222
```

### 输出

```
213
```

## 样例 #2

### 输入

```
3921
10000
```

### 输出

```
9321
```

## 样例 #3

### 输入

```
4940
5000
```

### 输出

```
4940
```

# 题解

## 作者：yaolibo (赞：6)

[题目链接](https://www.luogu.com.cn/problem/CF915C)
### 题意解释：
给定两个正整数a，b，要求重排a中的数字，问不超过b的a的最大值是多少。
### 思路 & 方法：贪心 + 递归
先将a中的数字从大到小排序，使得a最大，然后按照b的每一位去决定这一位应该放的数字，一旦发现没有数字可放时便递归往前找。
### 特殊情况：
（1）如果a的位数比b小，那么a就小于b，这是只用输出排列最大的a就行了；   
（2）如果答案某一位的数字比b的那一位小，无论后面的数字是多少，a就一定小于b，那么根据贪心策略，从这位开始，只需要输出后面剩下数字排列所得的最大值。   
#### 举个例子：a = “54321”，b = “45413”，i = 0， c = “”。  
**① i = 0，∵ a[1]为当前不大于b[i]的最大数字  ∴ c = “4”；**  
**② i = 1，∵ a[0]为当前不大于b[i]的最大数字  ∴ c = “45”；**  
**③ i = 2，∵ a[2]为当前不大于b[i]的最大数字 且 a[2] < b[i]，可见：**  
#### 453□□ < 45413，所以这时要取得最大数，只需把没有用过的数字1和2组成最大值，即21，放在答案末尾，所以答案为45321。
#### PS：具体细节见代码注释。 
------------
### Code：
```
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
char a[110], b[110]; //使用字符类型存放数字，方便操作
string c; //存储答案
int la, lb, i, j, k, vis[110]; //vis数组记录该数字是否用过
bool cmp(char e, char f) { return e > f; } //从大到小排序
void change(int x) { //递归修改答案
	char str = b[x];
	int i, j;
	c = c.substr(0, c.size() - 1); //将答案去掉最后一位数字
	for (i = 0; i < la; i++) { //遍历a的所有数字，重新寻找答案
		if (a[i] < str && !vis[i]) { //寻找不超过b[i]的第二大数字
			c += a[i];
			vis[i] = 1;
			break;
		}
	}
	for (j = 0; j < la; j++) //把之前找到的数字的标记取消
		if (a[j] == str && vis[j]) {
			vis[j] = 0;
			break;
		}
	if (i == la) change(x - 1); //如果依旧没找到答案，就再次修改前一位的答案
	else { //如果找到答案，因为找到的答案一定小于b[i]，于是直接输出剩下数字组成的最大数
		for (i = 0; i < la; i++)
			if (!vis[i])
				c += a[i];
		cout << c;
		exit(0);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0); //加速命令
	gets(a); gets(b);
	la = strlen(a); lb = strlen(b);
	sort(a, a + la, cmp); //先让a取最大值，也方便后面的贪心操作
	if (la < lb) { 
   		for (i = 0; i < la; i++)
        		cout << a[i];
		return 0;
	} //如果a的整体位数比b小的话，则直接输出最大的a就行了
	for (i = 0; i < lb; i++) { //遍历b的每一个数字
		for (j = 0; j < la; j++) { //遍历a的每一个数字，找到第一个小于等于b[i]的数字
        
			if (a[j] <= b[i] && !vis[j]) { //贪心！注意还要判断这个数是否被用过
				c += a[j]; //将这个数字放入答案中
				vis[j] = 1; //标记被使用过
				break; //找到第一个数字就马上跳出循环
			}
		}
		if (a[j] != b[i]) { //特判找到的数字不等于b[i]的情况
			if (j == la) //说明没有找到符合条件的数字，需要递归回头修改答案
				change(i - 1);
			else { //找到的数字小于等于b[i]，则直接输出剩下数字组成的最大数
				for (j = 0; j < la; j++)
					if (!vis[j])
						c += a[j];
				cout << c;
				return 0;
			}
		}
	}
	cout << c; //记得这里还要输出答案
	return 0;
}
```
### 结束~Over~

---

## 作者：Otue (赞：2)

来一发最短代码题解。
# 题目大意
现在，请你对 $a$ 进行重构，重新排列其各位数字顺序，得到一个不含前导 $0$ 的新正整数。

要求新正整数在不超过 $b$ 的前提下，尽可能大。
# 思路
第一种情况：当 $a$ 的位数小于 $b$ 的位数，直接把 $a$ 从大到小排序即可。（看看样例也知道嘛）

---

第二种情况：当 $a$ 的位数等于 $b$ 的位数。

那么从 $a$ 的第 $1$ 位开始枚举，对于每一位，可能取 $0\sim 9$ 这 $10$ 个数，肯定最先要取 $9$ ，但是如何判断取 $9$ 行不行呢？

定义一个 $res$ 表示当前数的值，拼上后面组成数的最小值，如果小于 $b$ 那么就是可行的。

比如：$a=123,b=222$，正在取第一位，我们要看看取 $3$ 行不行。易知 $res=3$，剩下的数还有 $2,3$ ，组成的最小数为 $23$，拼在一起 $323$，大于 $b$ ，故取 $3$ 不行。

# 代码
还不行，看代码吧..

![](https://s3.bmp.ovh/imgs/2022/03/cd04b900260b8bb0.png)

---

## 作者：zhanxianyun (赞：2)

~~那么好的题居然没有人搞玄学？~~

手把手教大家玩转贪（玄）心（学）

# 题意解释:
题目大意是说有输入两个不大于10的18次方的数（unsigned long long？）第一个数里面的数字可以随意交换位置（储存的时候就需要用字符串类型了），求出不超过第二个数的最小数。

例子：
第一个数1331

第二个数3152

答案：3131

# **思路：**
我在解释题意的时候就讲过用字符串类型来储存

首先想数据结构：既然位置没有关系，自然想到用桶存储第一个字符串，第二个字符串不用管它

然后考虑特殊情况

第一种：如果第一个字符串等于第二个字符串，那么直接输出原字符串就行了。（不超过的最大字符串啊）

第二种：如果这两个字符串长度不一样（或者说是第二个字符串的长度大于第一个字符串的长度），第一个字符串就不需要考虑如何变出不超过它的数，只用考虑如何变出最大的数，直接从大到小遍历桶，能输出就输出（第一个字符串变出来的最大的数）

考虑完之后就可以想如何变出不超过第二个字符串的最大数

既然要考虑如何变出一个不超过第二个数就最大的数，所以我们就应该从第二个字符串入手，要遍历第二个字符串

我们可以逐个拿出字符，然后去遍历桶，有没有小于等于这个字符数字在桶中，然后我们就可以把这个数字存到print数组里面，到时候一起数字就行了。

但是如果我们会遇到两个特殊情况

1.如果桶里面没有等于这个字符数，只有小于这个字符的数

{

这种情况十分简单，只要取出小于这个字符的数，剩下的数甚至比不用管，直接从大到小输出就行了。

}

2.如果桶里面连任何一个小于等于的字符数都找不到怎么办？

{

这时候我们就需要往回找，一直找到有比已经预定输出小的，然后再更换，剩下的不用管，直接从大到小输出就行

}

PS:桶里面持续保持着没用过的数

具体看代码吧
```c
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
const int N=30;
char s[N],str[N];
int a[10],beixuan[N],print[N];
void printend(int *a)
{
	for(int i=9;i>=0;i--)
	{
		while(a[i])
		{
			a[i]--;
			printf("%d",i);
		}
	}
	exit(0);
}
void printstart(int i,int *print)
{
	for(int j=0;j<=i;j++)
		printf("%d",print[j]);
}
bool same(char *s,char *str)//判断两个数是否相同
{
	int lens=strlen(s),lenstr=strlen(str);
	if(lens!=lenstr)return false;
	for(int i=0;i<lens;i++)
		if(s[i]!=str[i])return false;
	return true;
}
void theend(int fail)//往回找
{
	int stop;
	for(int i=fail-1;i>=0;i--)
	{
		if(beixuan[i]!=-1)//如果这个数的备选数组有数的话
		{
			stop=i;//直接停下来
			a[print[i]]++;//先把原来要输出的数放回数组里
			print[i]=beixuan[i];//最后替换成新的数
			a[beixuan[i]]--;//这个新的数要从桶里面丢掉
			break;//停下来
		}
		else a[print[i]]++;//如果这个数的备选数组没有数的话，就可以继续往回找，并且把现在这个数放回桶里面
	}
	printstart(stop,print)//把剩下的输出就行了啦;
	printend(a);
}
int main()
{
	scanf("%s",s);
	scanf("%s",str);
	int len=strlen(s);
	for(int i=0;i<len;i++)
		a[int(s[i]-'0')]++;//桶存
	memset(beixuan,-1,sizeof(beixuan));
	if(same(s,str))//如果两个数相同的话
    {
		printf("%s",str);
		return 0;
	}
	if(strlen(s)!=strlen(str))//如果长度不相等的话
	{
		printend(a);
	}
	len=strlen(str);
	for(int i=0;i<len;i++)//遍历第二个字符串
	{
		int pos=str[i]-'0';//取出现在要用的数字
		bool first=false,stop=false;;//first标记的是找不找得到，stop是可不可以直接结束，直接无脑从大到小输出
		for(int j=pos;j>=0;j--)
		{
			if(a[j]==0)continue;//如果桶里面没有这个数就跳过
			if(first)//如果找到过的话，把这个数加进备选数组里（备选数组就是如果一个小于等于的东西都找不到的话，就需要用到另外一个数）
			{
				beixuan[i]=j;
				break;
			}
			first=true;//其余情况就是第一次找到小于等于整数
			a[j]--;//取出标记
			if(!stop&&j!=pos)//如果他是小于这个数的话,stop标记为true
				stop=!stop;
			print[i]=j;//把它加进print数组里
		}
		if(stop)//如果满足停止条件的话，就可以输出了
		{
			printstart(i,print);
			printend(a);
		}
		if(!first)//如果一个小于等于得数都没有找到，就可以往回找
			theend(i);
	}
	printstart(len-1,print);//如果可以变到和原数一样的话
	printend(a);
    while(1);//杜绝抄袭你懂得~
}
```

完结撒花啦啦啦啦


---

## 作者：Apro1066 (赞：2)

我用的dfs搜索，不过直接dfs会超时。用C++STL的全排列函数更会TLE，所以剪枝是必要的。

注意，剪枝的方法不是我原创的！

```cpp
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
long long int num[11],s,len1,len2;
char c1[21],c2[21],c3[21];
void dfs(long long i,bool f)//i表示位，f用来判断是否有当前位小于c2的当前位 
{
	if(s)//如果有答案，返回即可，注意这个要写最前面 
	{
		return;
	}
	if(i==len1)//达到c1串，找到了一个可能的答案 
	{
		s=1;//标记记录 
		return;
	}
	register int j,k;
	for(j=9;j>=0;j--)//倒着遍历选取可以用的数字
	{
		if(num[j]!=0)//如果有数字 
		{
			if(f||c2[i]==j+'0')
			//如果前面已经有一个位是小于c2的对应的位了，那么后面的位只需要从大到小依次放入答案数组[剪枝，非原创]
			//如果相等也放入，反正有回溯，我们是找最优解 
			{
				num[j]--;//用这个数字，-1 
				c3[i]=j+'0';//答案串记录 
				dfs(i+1,f);//往下一位搜 
				if(s)//找到了答案就返回 
				{
					return;
				}
				num[j]++;//回溯，我们是找最优解，所以回溯是必要的 
			}
			else if(c2[i]>j+'0')//如果当前数小于b的对应位，直接放入即可，f记为1 
			{
				num[j]--;//这下面都同理 
				c3[i]=j+'0';
				dfs(i+1,1);
				if(s)
				{
					return;
				}
				num[j]++;
			}
		}
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	register long long int i,j;
	cin>>c1>>c2;
	len1=strlen(c1);
	len2=strlen(c2);
	if(len1<len2)//这里贪心了一下，如果c1比c2长度短 
	{
		sort(c1,c1+len1);//把c1排序即可 
		for(i=len1-1;i>=0;i--)//从大到小输出 
		{
			cout<<c1[i];
		}
		cout<<endl;
		return 0;//结束 
	}
	else//反之我们需要搜索找到最优方案 
	{
		for(i=0;i<len1;i++)//记录每个数字出现的次数 
		{
			num[c1[i]-'0']++;
		}
		dfs(0,0);
		for(i=0;i<len1;i++)
		{
			cout<<c3[i];
		}
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：hzoi_liuchang (赞：1)

### 分析

这道题可以用贪心解决，分为两种情况

1、$a$的位数小于$b$的位数，此时我们把$a$的所有位从大到小排一下序即可

2、$a$的位数和$b$的位数相等，那么$a$的最高位一定小于等于$b$的最高位

此时又可以分成两种情况

第一种即$a$的最高位填的数字比$b$的最高位填的数字小

我们把剩下的从大到小排一下序即可

另一种就是$a$和$b$最高位上的数字相等

我们可以选择一个满足条件的最大值填入$a$的第二位，对于其他位也是如此

这样看起来似乎没有什么问题，但是对于下面的这一组数据

> 15778899
98715689

如果我们用简单的贪心去匹配，那么$a$的前$5$位会分别被填上$98715$

匹配到第$6$位时，我们会发现此时没有合适的数字去匹配

因此，我们的贪心要能够支持回溯操作，即~~可持久化贪心~~

如果当前匹配不成功的话，那么回溯到上一状态继续匹配

时间复杂度$O(玄学)$

### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=25;
int a[maxn],cnt[maxn],ans[maxn],xn[maxn];
char s[maxn],s1[maxn];
signed main(){
	scanf("%s%s",s+1,s1+1);
	int len=strlen(s+1),len1=strlen(s1+1);
	for(int i=1;i<=len;i++) a[i]=s[i]-'0';
	if(len1>len){
		sort(a+1,a+1+len);
		for(int i=len;i>=1;i--) printf("%lld",a[i]);
		printf("\n");
		return 0;
	}
	int qnd=0;
	for(int i=1;i<=len;i++){
		cnt[a[i]]++;
		xn[a[i]]++;
	}
	//处理出每一个数字在原序列中出现的个数
	bool bishangyigeda;
	if(cnt[s1[1]-'0']){
		cnt[s1[1]-'0']--;
		ans[1]=s1[1]-'0';
		int j=2;
		bishangyigeda=0;
		while(j<=len1){
			bool jud=0;
			if(bishangyigeda==0){
				for(int k=s1[j]-'0';k>=0;k--){
					if(cnt[k]){
						cnt[k]--;
						ans[j]=k;
						jud=1;
						if(k!=s1[j]-'0')bishangyigeda=1;
						break;
					}
				}
			} else {
				for(int k=9;k>=0;k--){
					if(cnt[k]){
						cnt[k]--;
						ans[j]=k;
						jud=1;
						break;
					}
				}
			}
			if(jud==0) qnd=1;
			int now=j;
			while(qnd==1 && j>=2){
				cnt[ans[j-1]]++;
				j--;
				for(int k=ans[j]-1;k>=0;k--){
					if(cnt[k]){
						cnt[k]--;
						ans[j]=k;
						jud=1;
						if(k!=s1[j]-'0')bishangyigeda=1;
						break;
					}
				}
				if(jud==1) qnd=0;
			}
			if(j==1 && qnd==1) break;
			if(jud==1) qnd=0;
			j++;
		}
	}
	//判断a和b的最高位是否相等
	if(qnd==0 && xn[s1[1]-'0']){
		for(int i=1;i<=len1;i++) printf("%lld",ans[i]);
		printf("\n");
	} else {
		memset(ans,0,sizeof(ans));
		for(int i=s1[1]-'0'-1;i>=1;i--){
			if(xn[i]) {
				xn[i]--;
				ans[1]=i;
				break;
			}
		}
		int j=2;
		while(j<=len1){
			for(int k=9;k>=0;k--){
				if(xn[k]){
					xn[k]--;
					ans[j]=k;
					break;
				}
			}
			j++;
		}
		for(int i=1;i<=len1;i++) printf("%lld",ans[i]);
		printf("\n");
	}
	return 0;
}


```

---

## 作者：AE酱 (赞：1)

贪心。
把A中的数字从大到小排个序，优先考虑大的数字，从高位到低位看每一位能不能放。



##Code

```cpp
    #include <iostream>
    #include <algorithm>
    #include <cstring>
    #include <cstdio>
    #include <cmath>
    using namespace std;
    #define LL unsigned long long
    string As,Bs;
    LL dataA[30]={0};
    LL dataB[30]={0};
    LL dataC[30]={0};
    LL Asize,Bsize,Ans=0;
    string Res="";
    inline bool judge(string x,int pos){
        int P=Asize-1;
        for(int i=0;i<Asize;i++){
            if(i==pos) continue;
            if(dataA[i]!=-1){
                x[P]=(char)(dataA[i]+(int)'0');
                --P;
            }
        }
        if(x<=Bs) return true;
        else return false;
    }
    int main(){
        cin>>As;
        cin>>Bs;
        Asize=As.size();Bsize=Bs.size();
        for(int i=0;i<Asize;i++){
            dataA[i]=As[i]-'0';
        }
        for(int i=0;i<Bsize;i++){
            dataB[i]=Bs[i]-'0';
        }
        sort(dataA,dataA+Asize,greater<LL>());
        if(Bsize>Asize){
            for(int i=0;i<Asize;i++)
                cout<<dataA[i];
            cout<<endl;
            return 0;
        }
        for(int i=0;i<Asize;i++)
            Res+="0";
        for(int i=0;i<Asize;i++){
            for(int j=0;j<Asize;j++){
                if(dataA[j]==-1) continue;
                string mid=Res;
                mid[i]=(char)(dataA[j]+(int)'0');
                if(judge(mid,j)){Res=mid;dataA[j]=-1;break;}
            }
        }
        cout<<Res<<endl;
        return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF915C Permute Digits
## 题意
给出两个正整数 $a,b$。在十进制下重排 $a$，构造一个不超过 $b$ 的最大数，不允许有前导零，数据保证有解。
## 不超过+最大=贪心
考虑以不超过为基础构造一个最大的数，很显然答案最大就是 $b$。所以如果 $a$ 中能构造出 $b$，那么答案一定是最优的。\
而如果构造不出来 $b$ 呢？我们肯定就要构造一个尽可能接近 $b$ 的数。这就用到了一个经典的套路——按位贪心。\
具体的，我们从高到低考虑每一位的数字，如果能填 $b$ 中的这一位，我们肯定填它是最优的。\
如果不能填这一位，我们填小于 $b$ 中这一位的最大值肯定是最优的。并且后面的数字无论怎么填都是合法的，于是我们后面从大到小填一定是合法且最优的。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int mp[114];
string a,b;
string ans;
string sum,st;
int getl(int i){
    for(int j=i-1;j>=0;--j){
        if(mp[j])return j;
    }
    return -1;
}
int getr(int i){
    for(int j=i+1;j<=9;++j){
        if(mp[j])return j;
    }
    return -1;
}
void dfs(int id){
    if(id==b.size()){
        if(sum<=b){
            cout<<sum<<'\n';
            exit(0);
        }
        return;
    }
    if(mp[b[id]-'0']>0){
        sum+=b[id];
        mp[b[id]-'0']--;
        dfs(id+1);
        sum.erase(sum.size()-1);
        mp[b[id]-'0']++;
    }
    int w=getl(b[id]-'0');
    if(w==-1)return;
    sum+=char(w+'0');
    mp[w]--;
    for(int j=9;j>=0;--j){
        if(mp[j]){
            sum+=char(j+'0');
            mp[j++]--;
        }
    }
    cout<<sum<<'\n';
    exit(0);
}
int main(){
    cin>>a>>b;
    sort(a.begin(),a.end());
    for(char ch:a){
        mp[ch-'0']++;
    }
    if(a.size()<b.size()){
        reverse(a.begin(),a.end());
        cout<<a<<'\n';
        return 0;
    }
    dfs(0);
    return 0;
}
```

---

## 作者：JimmyLee (赞：0)

# 题意

>给出两个正整数 $a,b$。在十进制下重排 $a$，构造一个不超过 $b$ 的最大数，不能有前导零。允许不去重排 $a$。

# 分析

因为位数小于等于 19，考虑搜索。

开个桶维护 $a$ 中每个数码的个数，按位搜索即可。

每一位贪心地从大到小枚举，显然这是最优的。

最劣复杂度是 $O(a)$，但是因为最多有一个位置无法贪心选择，实际复杂度为 $O(\log a)$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

int cnt[10];
string a, b, det;

void dfs(int p, bool lead, bool up)
{
    if(!~p) cout<<det, exit(0);
    int mx=up?b[p]-'0':9;
    int mn=lead;
    for(int i=mx;i>=mn;i--)
    {
        if(!cnt[i]) continue;
        cnt[i]--;
        det+=i+'0';
        dfs(p-1, 0, up&&i==b[p]-'0');
        cnt[i]++;
        det.pop_back();
    }
}

int main()
{
    cin>>a>>b;
    reverse(b.begin(), b.end());
    if(a.size()<b.size())
    {
        sort(a.begin(), a.end(), greater<char>());
        return cout<<a, 0;
    }
    for(auto c:a) cnt[c-'0']++;
    dfs(a.size()-1, 1, 1);
}

```

---

## 作者：Ruan_ji (赞：0)

### 前言
这是一道搜索题。它具有很强的思考性，但是需要思考的点不多，所以是一道黄题。

### 思路
题面已经非常清楚了，这里就不再赘述了。我们直接看思路。

由于这是一道深搜的题目，所以我们使用较为清晰的步骤式思路。

1. $a$ 的数位比 $b$ 短的时候，$a$ 从大到小输出。因为数位都比 $b$ 少了，不管它如何变换都肯定不会比 $b$ 大，所以直接从大到小输出。

1. 统计 $a$ 的数字个数，对着 $b$ 来 ```dfs```。

1. ```dfs``` 表示放置 $i$ 位，记录之前是否已经比 $b$ 小（为了剪枝）。大家想一想，如果已经比 $b$ 小了，那么不管怎么输出都无妨。所以我们直接把剩下的数位从大到小输出，这是本题最重要的剪枝，好好理解。

1. ```dfs``` 进入时，先判断是否已经有解，有解跳出。

1. 如果放 ```lenb + 1``` 位，则代表放完了，输出。

1. 从 $9$ 到 $0$ 枚举，对于第 $i$ 位，如果我的小于标记是 1，那么我就放。

1. 如果前面没有小于标记，但是第 $i$ 位小于 ```b[i]```，置小于标记为1。

1. 如果第 $i$ 位比 ```b[i]``` 大，结束掉。

至此，我们的爆搜加剪枝执行完毕。

下面我们来看一看代码。

### 代码

提示：这道题目很锻炼代码能力，请不要抄袭题解，不到万不得已不要看代码部分。代码部分仅供参考。

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[25],b[25],c[25];
long long lena,lenb,num[11],s;
bool cmp(){
}
void dfs(long long i,bool f){
	if(s){
		return ;
	}
	if(i==lena){//找到答案
		s=1;
		return ; 
	}
	for(int j=9;j>=0;j--){
		if(num[j]!=0){
			if(f||j==b[i]-'0'){
				num[j]--;
				c[i]=j+'0';
				dfs(i+1,f);
				if(s){
					return;
				}
				num[j]++;
			}
			else if(j<b[i]-'0'){
				num[j]--; 
				c[i]=j+'0';
				dfs(i+1,1);
				if(s){
					return;
				}
				num[j]++;
			}
		}
	}
}
int main(){
	cin>>a>>b;
	lena=strlen(a);
	lenb=strlen(b);
	if(lena<lenb){//贪心 
		sort(a,a+lena);
		for(int i=lena-1;i>=0;i--){
			cout<<a[i];
		}
		cout<<endl;
	}
	else{
		for(int i=0;i<lena;i++){
			num[a[i]-'0']++; 
		}
		dfs(0,0);
		for(int i=0;i<strlen(c);i++){
			cout<<c[i];
		}
	}
	return 0;
} 
```


---

