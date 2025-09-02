# [ARC005A] 大好き高橋君

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc005/tasks/arc005_1

 高橋君は自分が大好きなので、自分の評判を調べるために自分の名前が入っているツイートを調べたいと考えました。しかし彼のフォロー数は多いので、タイムラインを $ 1 $ つずつ確認して自分に関係あるつぶやきを探すのは面倒です。  
  
 そこで高橋くんを手伝うために、与えられる文から高橋君を表す単語が現れる回数を数えてください。  
 ただし、単語の一部に高橋君を表す単語を含んでいた場合も、高橋君を表す単語と完全に一致しない限り、その単語を高橋君を表す単語として数えないでください。  
  
 以下の3単語が高橋君を表す単語です。

- TAKAHASHIKUN（高橋君をヘボン式ローマ字にして、全て大文字にしたもの）
- Takahashikun（高橋君をヘボン式ローマ字にして、先頭の $ 1 $ 文字のみ大文字、残りは小文字にしたもの）
- takahashikun（高橋君をヘボン式ローマ字にして、全て小文字にしたもの）
 
 入力は以下の形式で標準入力から与えられる。 > $ N $ $ w_{0} $ $ w_{1} $ … $ w_{N-1} $.

- 入力は $ 2 $ 行ある。
- $ 1 $ 行目には、$ 2 $ 行目に与えられる文に含まれる単語数を表す整数 $ N(1≦N≦50) $ が与えられる。
- $ 2 $ 行目には $ 2 $ 文字以上 $ 100 $ 文字以下の $ 1 $ 文が与えられる。 
  - 文は単語 $ w_i(0≦i≦N-1) $から成り、各単語は空白で区切られている。
  - 最後の単語 $ w_{N-1} $ の後には空白を挟まず `.` がある。
  - 単語 $ w_{i}(0≦i≦N-1) $ は英字(`A-Z`, `a-z`)で成り立っている。

 与えられた文の中で高橋君を表す単語が現れる回数を標準出力に $ 1 $ 行で出力せよ。  
 なお、最後には改行を出力せよ。 ```

5
Takahashikun is not an eel.
```

 ```

1
```

- Takahashikun が $ 1 $ 回現れます。
 
```

5
TAKAHASHIKUN loves TAKAHASHIKUN and takahashikun.
```

 ```

3
```

- TAKAHASHIKUN が $ 2 $ 回、takahashikun が $ 1 $ 回現れるので $ 2+1=3 $ が答えです。

```

6
He is not takahasikun but Takahashikun.
```

 ```

1
```

- Takahashikun が $ 1 $ 回現れます。
- takahasikun は takahashikunではないので、高橋君を表す単語ではありません。
 
```

1
takahashikunTAKAHASHIKUNtakahashikun.
```

 ```

0
```

- 単語の一部に高橋君を表す単語が含まれていても、高橋くんを表す単語そのものでなければ当てはまりません。
 
```

18
You should give Kabayaki to Takahashikun on July twenty seventh if you suspect that he is an eel.
```

 ```

1
```

- Takahashikun が $ 1 $ 回現れます。

# 题解

## 作者：yuzhechuan (赞：12)

高桥名字其实有6种情况，带句号的三种，不带的三种

------------

```cpp
#include <bits/stdc++.h>//万能库
using namespace std;
int n,ans;
string s;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	cin>>s;//读到下一个换行为止
    	if(s=="TAKAHASHIKUN"||s=="Takahashikun"||s=="takahashikun"||s=="TAKAHASHIKUN."||s=="Takahashikun."||s=="takahashikun.")//依次枚举6种情况就好了
    		ans++;//答案加1
	}
	cout<<ans;//输出
	puts("");//换行
}
```

---

## 作者：Bilibili乾杯Ω (赞：3)

这一题其实不难，但是很难一次全AC。
为何？

因为这道题有很多的
## 坑！！！
（且难以察觉）

比如：输出空行，文末句号"."以及string。~~亲测，说多了都是泪~~~

并且，题目翻译错了一处！！！（嘤嘤嘤）

话不多说，上代码，其实不难。
```cpp
#include<bits/stdc++.h>  //万能头
using namespace std;
long long n,ans;
string a;  //要用string
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
	    if(a=="TAKAHASHIKUN"||a=="TAKAHASHIKUN."||a=="Takahashikun"||a=="Takahashikun."||a=="takahashikun"||a=="takahashikun.") ans++;  //核心部分，判断
	}
	cout<<ans<<endl;
    return 0;  //结束
}
```

---

## 作者：jinhangjie2006 (赞：3)

```pascal
var
 i,j,c,d,e,b,n,m:longint;
 s1,s2,s3:string;
 s:array[1..100000] of string;//用来储存每一个单词 
 ch:char;
begin
 readln(n);
 i:=1;
 while (not eoln) do //这个函数的作用是 直到你输入完毕 点击回车了 他自动结束输入
  begin
   read(ch);//字符一个一个读入
   if (ch<>' ') and (ch<>'.') then s[i]:=s[i]+ch//他如果是一个字母 就把它加进s数组里 如果不是字母就不能加了，就表示一个新的单词开始了 i:=i+1,当然‘.’不能算单词的一部分 所以不可以加上去
     else
      i:=i+1;
  end;
 for j:=1 to i do
  if (s[j]='TAKAHASHIKUN') or (s[j]='Takahashikun') or (s[j]='takahashikun') then e:=e+1;//所有单词都存进s数组里了 然后判断一下他是不是代表高桥君的单词就行了；
 writeln(e);
end.
```

---

## 作者：不到前10不改名 (赞：1)

```
#include<stdio.h>
#include<iostream>
using namespace std;
int n,i,s;
string a;//也不给用char，急死我个纯c党了
int main()
{
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {cin>>a;//不知为何这东西吃scanf...（gets更惨）
    if(a=="TAKAHASHIKUN"||a=="Takahashikun"||a=="takahashikun"||a=="TAKAHASHIKUN."||a=="Takahashikun."||a=="takahashikun.")//亲自实验确实是6种
    s++;}
    printf("%d\n",s);//回车
    return 0;
}
```

---

## 作者：stry (赞：0)

其实这一题只需要依次判断是否是
```cpp
1.TAKAHASHIKUN
2.Takahashikun
3.takahashikun
4.TAKAHASHIKUN.
5.Takahashikun.
6.takahashikun.
```
就行了

~~这题不应该过水隐藏吗~~

~~代码，还需要吗？~~
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,ans;
string s;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s=="TAKAHASHIKUN"||s=="Takahashikun"||s=="takahashikun"||s=="TAKAHASHIKUN."||s=="Takahashikun."||s=="takahashikun.")//依次枚举
            ans++;
    }
    cout<<ans<<endl;//这题一定要记得换行
}
```
若本蒟蒻有不足之处，请各位大佬指点，谢谢！


---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题真的符合红题，仅仅只是简单字符串处理的题目。好吧，废话不多说，代码来一波！

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int n,s;
    string a[1000000];//定义变量
    int main()
    {
    cin>>n;//读入n
    for(int i=1; i<=n; i++)
    {
        cin>>a[i];//读入当前字符串
        if(a[i]=="TAKAHASHIKUN"||a[i]=="Takahashikun"||a[i]=="takahashikun")s++;//如果符合题目要求，累加器加1
        else
        {
            a[i].erase(a[i].size()-1,1);
            if(a[i]=="TAKAHASHIKUN"||a[i]=="Takahashikun"||a[i]=="takahashikun")s++;
            //如果符合的字符串多了句号，先删掉句号，再比较，如果符合，累加器加1
        }
    }
    cout<<s<<endl;//输出结果并换行
    return 0;//要有好习惯
    }
    
# AT不换行，爆零两行泪
好了，本蒟蒻就讲到这里，希望对读者有所帮助


---

## 作者：趣味的吃 (赞：0)

Takahash      **ikun**（要素察觉）

#### 鸡你太美~

咳咳让我们回归正题。

大家好这里是在AT水题的趣味的吃，让我们冷静分析一下这道题。

1. 在这道题中，n其实啥用没有，惊喜不？因为C++的string可以直接进行判断，并不需要读入几个字符，所以忽略掉即可

2. 仔细阅读输入输出样例#2和#3，你发现了什么？Takahashikun后面加了个句号，而这个仍然算作一个名字。所以带句号的三种情况也要进行判断。（看到题解里面有人WA了以后才看到hhh）

3. cin循环读入，然后判断是否符合条件，符合计数器加1即可

思路讲完了。大家可以自己写代码去了。



------------
啥？这个大水题宁还不会？

emm，好吧，AC代码奉上，切勿直接抄袭，思考最重要

```cpp
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    int sum=0;
    while(cin>>s)
    {
        if(s=="TAKAHASHIKUN" || s=="Takahashikun" || s=="takahashikun" || s=="TAKAHASHIKUN." ||s=="Takahashikun." || s=="takahashikun." )
        {
            sum++;
        }
    }
    cout<<sum<<endl;
    return 0;
}
```


---

## 作者：百里亦守约 (赞：0)

# 解题思路：
根据题意，可以知道，这道题是一道关于字符串的题，而且看过了数据，就知道了每一次输入一个句子，而且遇到TAKAHASHIKUN、Takahashikun
、Takahashikun就说明要记录一次，观察数据，我们可以知道是输入一个句子，所以当最后出现了那些词的话那么可以说明如果那些单词带**句号**，如果带句号的话那么这个词就会在后面有一个**点**，然后我们就可以知道这道题就变成了六种情况了。分别是带点的和不带点的：（前面三种是不带点的，后面三种是带点的）**TAKAHASHIKUN**、**Takahashikun**、**Takahashikun**、**TAKAHASHIKUN.**、**Takahashikun.**、**Takahashikun.**
。**~~所以我们可以根据这种做法来求出到底有几个字符串有这种标志词了。~~**
# 解题方法：
可以先赋值好到标志词，防止在后面要打一串非常长的if，打完之后就可以在输入时快速找出这个字符串是否带有这些东西然后再计入一个变量中就可以了。
# 程序代码如下：
```
#include<bits/stdc++.h> //头文件
using namespace std;
int o,n,ans;
string st;
string x[100005]; //定义(只用定义到7即可）
int main()
{
    x[1]="TAKAHASHIKUN";
    x[2]="takahashikun";
    x[3]="Takahashikun";
    x[4]="Takahashikun.";
    x[5]="takahashikun.";
    x[6]="TAKAHASHIKUN."; //先赋好值，方便等会求出结果
    cin>>n; //输入n
    for(int i=1;i<=n;i++)
    {
        cin>>st; //边循环边输入字符串
        o=0; //判断这个字符串有没有高桥君的出现的标记。
        for(int j=1;j<=6;j++)
            if(st==x[j]) o=1; //如果有的话，那么就要做好标记
        if(o==1) ans++; //如果标记到了，那么就要加一
    }
    cout<<ans<<endl; //输出记得换行。
    return 0;
}
```


---

## 作者：不存在之人 (赞：0)

高桥君的名字一共有6种情况，分别是："TAKAHASHIKUN"、"Takahashikun"、"takahashikun"、"TAKAHASHIKUN."、"Takahashikun."以及"takahashikun."。（注意：高桥君的名字有可能后面有一个“.”）

当我们知道了以上6种情况后，代码中只需要6个if语句判断一下，暴力穷举一下就行了。
```cpp
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
int main()
{
	int n,ans=0;
	string s;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s=="TAKAHASHIKUN")
            ans++;
		if(s=="Takahashikun")
			ans++;
		if(s=="takahashikun")
			ans++;
		if(s=="TAKAHASHIKUN.")
			ans++; 
		if(s=="Takahashikun.")
			ans++;
		if(s=="takahashikun.")
			ans++;
    }
    printf("%d\n",ans);
}
```

---

## 作者：Jinyeke (赞：0)

### 题目大意：给出NN 个由大小写字母组成的、长度大于22 小于100100 的字符串,输出其中有几个字符串代表高桥君

高桥君可以由这三个字符串代表

TAKAHASHIKUN

Takahashikun

Takahashikun
（感谢@保登心爱 提供的翻译）
#### 其实这题用一个函数upcase（将一个字符串中的小写字符转成大写)，就可以值判断一个啦，以下为代码（pascal）
```pascal
 var
  a,t:string;
  s,i:longint;
 begin
  readln(i);
  read(a);
  i:=1;t:='';
  while a[i]<>'.' do 
   begin
    if a[i]<>' ' then t:=t+a[i]
     else 
      begin 
       if upcase(t)='TAKAHASHIKUN' then                 inc(s);t:='';
      end;
     inc(i);
   end;
   writeln(s);
 end.
```
But，当我满怀信心提交时，WA！后来我找了一下，因为我是靠字符串后面的‘ ’来判断的，但是最后一个字符串如果按我的方法是忽略不计的，所以我们要手动把字符串后面的'.'，改成' .'(前面有空格），代码如下（pascal)
```pascal
var
  a,t:string;
  s,i:longint;
 begin
  readln(i);//其实在我的方法里没啥用，所以就随便找个变量输进去
  read(a);//输入字符串（注意：不要妄想用一个数组输入n个字符串，由于字符串里可能含有空格，所以一般只有在换行的情况下才会输入字符串数组）
  i:=1;t:='';//i要为1，t要为空串
  a[length(a)]:=' ';//加空格
  a:=a+'.';//加'.'
  while a[i]<>'.' do //没结尾之前
   begin
    if a[i]<>' ' then t:=t+a[i]//不等于空格就一只加
    else begin if upcase(t)='TAKAHASHIKUN' then inc(s);t:='';end;
    //等于空格就判断一下前面加起来的转为大写是不是等于'TAKAHASHIKUN'，然后不管是否成立，t先清零
    inc(i);//累加i（不然就死循环啦！）
   end;
   writeln(s);//输入符合条件的字符串的数量（注意：AT大坑，换行输出！）
   end.
```
### 共建文明洛谷，请勿Ctrl+C！


---

## 作者：Luisvacson (赞：0)

# STL-MAP最简单
~~STL大法好~~

~~（不接受任何反驳）~~

直接上代码：（takahashikun后面加句号也算啊喂）
```cpp
#include<bits/stdc++.h>
#define for(i,a,b) for(int i=a;i<=b;i++)
#define _inline __inline__ __attribute__((always_inline))
using namespace std;
template<class T> _inline void read(T &x){
	T res=0,f=1;
	char c=getchar();
	if(c=='-') f=-1;
	while(c>'9'||c<'0') c=getchar();
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	x=res*f;
}  //输入优化，看不懂自行忽略
template<class T> inline void print(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}  //输出优化，同上
map<string,bool> mp;
  //重点来了，把string型映射到bool数组上去，就可以以字符串作为数组下标
int main(){
	mp["TAKAHASHIKUN"]=true;
	mp["Takahashikun"]=true;
	mp["takahashikun"]=true;
	mp["TAKAHASHIKUN."]=true;
	mp["Takahashikun."]=true;
	mp["takahashikun."]=true;
  //直接预处理，不要忘句号
  //因为STL定义在全局，所以没处理的自动为false
	int n;
	read<int>(n);//输入n
	string s;
	int cnt=0;
	while(n--){
		cin>>s;
		if(mp[s]) cnt++;
	}//非常好理解
	print<int>(cnt);//输出cnt
	puts("");//岛国不要忘换行
	exit(0);
} 
```
~~话说AT题目都这么水的吗~~

---

