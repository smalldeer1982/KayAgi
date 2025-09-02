# [ARC002C] コマンド入力

## 题目描述

输入指令

高桥君和朋友玩了格斗游戏。

他们玩的游戏的规则是：手柄上有四个键：A、B、X、Y，按照顺序连续按下一定的按键序列，就可以发动连续技。

然而，高桥君平时都不怎么玩格斗类游戏，所以他被朋友吊打了。

手柄上还有两个按键L、R，可以当快捷键使用。L和R都可以代替任意连续的两个按键，加入快捷键就可以让发动连续技的所需按键次数变小。

举个栗子：有一个连续技要求连续按顺序按下：ABXY，这需要按四次；然而，如果设置L=AB，R=XY，这样连续按顺序按下LR就可以发动同样的连续技，这只需要按两次，简化了操作。

高桥君想赢，他想知道一个连续技的指令最少需要按键多少下才能打出。

# 题解

## 作者：yukimainyan (赞：5)

一共就4个字母，快捷键的可能方案只有16种，分别枚举L和R可能的情况，循环的次数也只有16的平方，不会超时，所以可以靠暴力枚举来做。

贴代码
```cpp
#include <iostream>
#include <string>
using namespace std;

const string data[16]={"AA","AB","AX","AY","BA","BB","BX","BY","XA","XB","XX","XY","YA","YB","YX","YY"};//先列出所有可能快捷键组合

int main(){
	string s;
	int n,ans;
	cin >> n >> s;
	ans=n;//最长也只能到n
	for(int i=0;i<16;i++){
		for (int j=0;j<16;j++){
			string L=data[i],R=data[j],temp=s;//枚举所有可能的L和R，注意每次替换前要还原被处理的指令串
			while(temp.find(L)!=-1){
				temp.replace(temp.find(L),2,"L");
			}//不停地在指令串里找L对应的指令并替换成一个字母L
			while(temp.find(R)!=-1){
				temp.replace(temp.find(R),2,"R");
			}//同上
			if (temp.length()<ans)
				ans=temp.length();//更新答案
		}
	}
	cout << ans << endl;//Atcoder的题目输出答案末尾需要换行，否则按WA算
	return 0;
}
```


---

## 作者：baogeger (赞：3)

一共有4*4=16种情况，都枚举一遍就好了

AC代码：
```c
#include<bits/stdc++.h>
using namespace std;
string w[16];
string L="L";
string R="R";

void db(){//枚举出所有情况
	string a[4];
	a[0]="A";
	a[1]="B";
	a[2]="X";
	a[3]="Y";
	int n=0;
	for(int x=0;x<=3;x++){
		for(int y=0;y<=3;y++){
			w[n]=a[x]+a[y];
			n++;
		}
	}
}

int main(){
	db();
	int n;
	cin>>n;
	string a;
	cin>>a;
	string b=a;
	int min=n;
    
	for(int x=0;x<=15;x++){
		for(int y=0;y<=15;y++){//16*16种不同的情况
			a=b;
			while(a.find(w[x])!=-1 )//查找{
				a.replace(a.find(w[x]),2,"L");//替换为“L”
			}
			while(a.find(w[y])!=-1 )//查找{
				a.replace(a.find(w[y]),2,"R");//替换为“R”
			}
			int sum=a.length() ;
			if(min>sum) min=sum;//比较得结果
		}
	}
	cout<<min<<endl;
	return 0;
}
```


---

## 作者：LiveZoom (赞：1)

# 题解 AT55 【コマンド入力】

这是一道模拟水题。

## 怎么处理这些快捷键？

由于并没有给出你的这些快捷键，我们就只能自己一个一个暴力枚举。为了方便枚举，我们用数字$1$代替$\text{A}$，数字$2$代替$\text{B}$，数字$3$代替$\text{L}$，数字$4$代替$\text{R}$。

## 代码实现

预处理：

```cpp
for (int i = 1; i <= n; ++i) {
	if (s[i - 1] == 'A') num[i] = 1;//num表示对应编号
	if (s[i - 1] == 'B') num[i] = 2;
	if (s[i - 1] == 'X') num[i] = 3;
	if (s[i - 1] == 'Y') num[i] = 4;
}
```

算答案：

```cpp
for (int i = 1; i <= 4; ++i) {//枚举快捷键编号
	for (int j = 1; j <= 4; ++j) {
		for (int x = 1; x <= 4; ++x) {
			for (int y = 1; y <= 4; ++y) {
				res = n;//初始值设为n
				int num1[100005];
				for (int k = 1; k <= n; ++k) num1[k] = num[k];//注意这里后面需要更改，所以要拷贝一份。
				for (int k = 1; k <= n; ++k) {
					if (num1[k] == i && num1[k + 1] == j || num1[k] == x && num1[k + 1] == y) num1[k] = num1[k + 1] = 0, res--;//前面的判断就是判断是否连续两个编号是i,j或者x,y。注意：这里的num1[k]和num1[k+1]一定要清零，否则如果num1[k+1]和num1[k+2]也可行就会少算答案
				}
				ans = min(ans, res);//取最小值
			}
		}
	}
}

```

其余的就不用讲了吧。

[提交记录](https://atcoder.jp/contests/arc002/submissions/16941859)

# The end

求通过

---

## 作者：eEfiuys (赞：0)

题目：[AT55](https://www.luogu.com.cn/problem/AT55)

暴力枚举所有 $l$ 和 $r$。每次从前往后扫一遍，扫到字符 $i$ 时，如果字符 $i$ 和字符 $i+1$ 构成 $l$ 或 $r$，那么跳过字符 $i+1$。取所有情况的最小值即可。时间复杂度 $O(4^4 \times n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
int ans=1e9;
char ch[4]={'A','B','X','Y'};
int f(char l1,char l2,char r1,char r2){
	int cnt=0;
	for(int i=0;i<n;i++){
		cnt++; //字符i没有和字符i-1构成l或r，那么答案+1。
		if(i==n-1)break; //防止越界。
		if((s[i]==l1&&s[i+1]==l2)||(s[i]==r1&&s[i+1]==r2))i++; //字符i和字符i+1构成l或r，那么跳过字符i+1。
	}
	return cnt;
}
signed main(){
	cin>>n>>s;
   //枚举所有情况。
	for(int il=0;il<4;il++)
		for(int jl=0;jl<4;jl++)
			for(int ir=0;ir<4;ir++)
				for(int jr=0;jr<4;jr++){
					if(il==ir&&jl==jr)continue; //l和r一样就跳过，去掉也行。
					ans=min(ans,f(ch[il],ch[jl],ch[ir],ch[jr])); //去最小值。
				}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：千城_Dhmc (赞：0)

## 本题思路：

由于并没有给出你的这些快捷键，我们就只能自己**暴力枚举**。

为了方便枚举，我们**用数字1代替 A**，**数字2代替 B**，**数字3代替 L**，**数字4代替 R**。

这一题就是**找出重复最多的两个连击键**，然后把这些键加起来的**和除2**就行了。
## 下面附上AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,res,num[10005];
string s;
int main(){
	int n;
	cin>>n>>s;
	ans=res=s.size();
	for (int i=1;i<=n;i++){
		if (s[i-1]=='A'){
			num[i]=1;
		}
		if (s[i-1]=='B'){
			num[i]=2;
		}
		if (s[i-1]=='X'){
			num[i]=3;
		}
		if (s[i-1]=='Y'){
			num[i]=4;
		}
	}
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			for(int x=1;x<=4;x++){
				for(int y=1;y<=4;y++){
					res=n;
					int num1[100005];
					for(int k=1;k<=n;k++){
						num1[k]=num[k];
					}
					for(int k=1;k<=n;k++){
						if(num1[k]==i&&num1[k+1]==j||num1[k]==x&&num1[k+1]==y){
							num1[k]=num1[k + 1]=0;
							res--;
						}
					}
					ans=min(ans,res);
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
本人第一次交题解，别喷，求通过。

---

## 作者：李若谷 (赞：0)

枚举L和R的所有可能
并找出最小长度的
```cpp
#include <iostream>
using namespace std;
string s;//字符串 
string a[16] = {"AB","BA","AX","XA","AY","YA","BX","XB","BY","YB","XY","YX","AA","BB","XX","YY"}; //记录全部可能的组合 
int Min = 1000;
int main(){
	int n;
	cin>>n;
	cin>>s;
	
	string L,R;
	for(int i=0;i<16;i++){
		for(int j=0;j<16;j++){ //枚举L和R。i,j是在a字符串中的编号 
			if(i == j)//相等就跳过，因为相等绝对不会比不同好 
				continue;
			int count = 0;  
			L = a[i];
			R = a[j];

			for(int k=0;k<s.size();k++){ 
			    if(s[k] == L[0]&&s[k+1] == L[1]){//如果s[k]还有s[k+1]组成的字符串等于L 
					count++;//数量+1 
					k++;//其实是+2但是由于for已经+1所以k++就行了 
				}
				else if(s[k] == R[0]&&s[k+1] == R[1]){//同理判断R 
					count++;
					k++;
				}
				else//如果不是L也不是R，那k就不加了，直接加数量 
					count++;
				
			}
			if(count<Min)
				Min = count;
		}
	}
	cout<<Min<<endl;//一定要换行，不然会错 
	return 0;
}

```



---

## 作者：nanatsuhi (赞：0)

~~连我这种蒟蒻都能水出一篇题解，这道题A掉岂不美哉~~

思路：暴力枚举。

这道题的按键一共才ABCD四个，L和R的可能性只有4的4次方种。

给的连招长度也只有1000，所以这道题显然是道暴力。~~连招长度1000这是什么神奇的招数~~

解法很简单：枚举每一种L和R的可能情况，然后在连招串中顺序枚举，如果接下来的两个字符为L或R就让顺序向前跳一位即可。依次更新答案。

实现看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s,t="ABXY"; 
int main()
{
	cin >>n>>s;
	int ans=n;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				for(int m=0;m<4;m++)  //四重循环枚举L和R
				{
					string l=t.substr(i,1)+t.substr(j,1);
					string r=t.substr(k,1)+t.substr(m,1);
					int tmp=0;
					for(int pos=0;pos<n;pos++,tmp++)
						if(pos<n-1&&(s.substr(pos,2)==l||s.substr(pos,2)==r)) pos++; //substr:从指定位置截取指定长度字符串，这里是跳位操作
					ans=min(ans,tmp);  //更新答案
				}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：Harry_8810 (赞：0)

####  **题目分析**         
题目中的按键只有四个，而快捷键有$16^2$也就是196种排列，所以直接暴力模拟就可以过      。          
#### 算法                     
第一步是直接开两个嵌套的for循环，用于枚举两个快捷键所代表的键位，接着在循环里算出使用这两个快捷键后需要的按键次数，最后取最小值输出即可

所以问题就转化成了怎样算出使用快捷键后的按键次数，我们先开一个循环，遍历输入的字符串，此时我们可以定义一个string变量，在里面存入当前字符和下一个字符，看该字符串是否与快捷键相等，如果相等就可以将答案减一，循环结束时我们就能得到最终答案。（注：有些细节详见代码注释                           
#### 贴上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string kuai[16]={"AA","AB","AX","AY","BA","BB","BX","BY","XA","XB","XX","XY","YA","YB","YX","YY"};//先枚举出快捷键的排列组合 
int main()
{
	int n;
	scanf("%d",&n);//输入长度 
	string in;
	cin>>in;//输入字符串 
	int Long=in.size(),Min=100000;
	for(int i=0;i<16;i++)//枚举第一个快捷键 
	{
		for(int j=0;j<16;j++)//枚举第二个快捷键 
		{
			int ans=Long;//答案的初始化，注意现在还没有处理 
			for(int k=0;k<Long-1;k++)//开始逐一遍历字符串 
			{
				string a;//定义子串，取当前两位 
				a+=in[k];//C++中的string支持直接加 
				a+=in[k+1];
				if(a==kuai[i])ans--,k++;//如果当前两位与枚举到的快捷键相同，则将答案减一，k++是防止重复 
				else//防止重复 
				{
					if(a==kuai[j])ans--,k++;//同理 
				}
			}
			Min=min(Min,ans);//取最小值，更新答案 
		}
	}
	printf("%d",Min);//愉快地输出 
	return 0;//潇洒地结束程序 
}
```
~~PS.本人萌新第一次写题解，求过~~~

---

