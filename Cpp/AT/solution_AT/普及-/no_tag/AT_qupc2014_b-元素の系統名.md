# 元素の系統名

## 题目描述

[problemUrl]: https://atcoder.jp/contests/qupc2014/tasks/qupc2014_b

原子番号を与える．それに対応する「元素の系統名（げんそのけいとうめい）」を出力せよ． 「元素の系統名」とは、原子番号の各位を、以下の表にしたがって綴ったものである。 また、一文字目は大文字で表記する。 あなたの仕事は元素番号が117番以降の3桁の元素の名前をつけることである。

数字綴り（1の位以外）綴り（1の位）0nilnilium1ununium2bibium $ * $3tritrium $ * $4quadquadium5pentpentium6hexhexium7septseptium8octoctium9enn $ * $ennium $ * $印が付いている表記について 注意が必要である "bi"または"tri"が"ium"と連結する場合は連続する"ii"は"i"と表記する。"enn"が"nil"または"nilium"と連結する場合は連続する"（e）nn"は"（e）n"と表記する 入力は以下の形式で与えられる。 > $ N $

 Nは原子番号である。 入力中は各変数はすべて整数である。また、以下の制約を満たす。 - $ 117≦N≦999 $
 
 元素の系統名（げんそのけいとうめい）を一行で出力してください ```
<pre class="prettyprint linenums">
145
```

 ```
<pre class="prettyprint linenums">
Unquadpentium
```


```
<pre class="prettyprint linenums">
902
```

 ```
<pre class="prettyprint linenums">
Ennilbium
```

# 题解

## 作者：死神审判 (赞：5)

### 思路：这题用字符串$string+$打表会更方便些，但是有许多的坑。
### 解法：
输入一个字符串，再输出每一位所对应的原子序数。

先判断百位，百位的坑在于开头的字母需大写。

放进一个$string$类型的表里，百位的数是什么，就输出对应的原子序数。

再判断十位，十位的坑在于这个$nil$和$il$，需特判。

把原子序数放进一个新的$string$类型的表里，十位的数是什么，就输出对应的原子序数。

个位与十位基本相同，表也只需用同一个，需特判。

最后是词尾，坑在于$um$和$ium$，需特判。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[10]={"Nil","Un","Bi","Tri","Quad","Pent","Hex","Sept","Oct","Enn"};
string b[10]={"nil","un","bi","tri","quad","pent","hex","sept","oct","enn"};//打表
int main(){
	string s;
	cin>>s;
	cout<<a[s[0]-'0'];
	if(s[1]=='0'&&s[0]!='9')cout<<"nil";
	else if(s[1]=='0'&&s[0]=='9')cout<<"il";
	else cout<<b[s[1]-'0'];//特判
	if(s[2]=='0'&&s[1]!='9')cout<<"nil";
	else if(s[2]=='0'&&s[1]=='9')cout<<"il";
	else cout<<b[s[2]-'0'];//特判
	if(s[2]=='2'||s[2]=='3')cout<<"um\n";
	else cout<<"ium\n";//特判
	return 0;
}
```



---

## 作者：infinities (赞：3)

对于此题，我只想也只能说呵呵，又是一道练习暴力的~~好~~题，此题唯一考察的就是审题能力，就是这几条：

1.首字母大写，要在词尾加-ium（具体为什么貌似是规定）

2.当尾数是2(-bi)或3(-tri)的时候，因词尾的字母“i”与-ium最前方的“i”重复，故其中的“i”应省略不写。

3.当9(-enn）后面接的是0(-nil)时，应省略三个n中的一个，只写两个。

在没好好看题之前，我打出了这个代码，信心满满地提交（非正解，别忙着抄）【其中分离数位的代码：a/100,(a/10)%10,a%10。楼上也有，可以自己看】：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a;
    cin>>a;
    if(a/100==1)cout<<"un"  ;else
    if(a/100==2)cout<<"bi"  ;else
    if(a/100==3)cout<<"tri" ;else
    if(a/100==4)cout<<"quad";else
    if(a/100==5)cout<<"pent";else
    if(a/100==6)cout<<"hex" ;else
    if(a/100==7)cout<<"sept";else
    if(a/100==8)cout<<"oct" ;else
    if(a/100==9)cout<<"enn" ;//首位的暴力
    
    if((a/10)%10==0)cout<<"nil" ;else
    if((a/10)%10==1)cout<<"un"  ;else
    if((a/10)%10==2)cout<<"bi"  ;else
    if((a/10)%10==3)cout<<"tri" ;else
    if((a/10)%10==4)cout<<"quad";else
    if((a/10)%10==5)cout<<"pent";else
    if((a/10)%10==6)cout<<"hex" ;else
    if((a/10)%10==7)cout<<"sept";else
    if((a/10)%10==8)cout<<"oct" ;else
    if((a/10)%10==9)cout<<"enn" ;//第二位的暴力
    
    if(a%10==0)cout<<"nil" ;else
    if(a%10==1)cout<<"un"  ;else
    if(a%10==2)cout<<"bi"  ;else
    if(a%10==3)cout<<"tri" ;else
    if(a%10==4)cout<<"quad";else
    if(a%10==5)cout<<"pent";else
    if(a%10==6)cout<<"hex" ;else
    if(a%10==7)cout<<"sept";else
    if(a%10==8)cout<<"oct" ;else
    if(a%10==9)cout<<"enn" ;//第三位的暴力
    
    cout<<"ium"<<endl;
    return 0;
}
```
然而却全WA了，~~这是为什么呢~~，因为没看题，所以在好好看了一遍题之后，我又打出了一个几乎没什么改动的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a;
    cin>>a;
    if(a/100==1)cout<<"Un"  ;else
    if(a/100==2)cout<<"Bi"  ;else
    if(a/100==3)cout<<"Tri" ;else
    if(a/100==4)cout<<"Quad";else
    if(a/100==5)cout<<"Pent";else
    if(a/100==6)cout<<"Hex" ;else
    if(a/100==7)cout<<"Sept";else
    if(a/100==8)cout<<"Oct" ;else
    if(a/100==9&&(a/10)%10!=0)cout<<"Enn" ;else
    if(a/100==9&&(a/10)%10==0)cout<<"En"  ;//首位的暴力
    
    if((a/10)%10==0)cout<<"nil" ;else
    if((a/10)%10==1)cout<<"un"  ;else
    if((a/10)%10==2)cout<<"bi"  ;else
    if((a/10)%10==3)cout<<"tri" ;else
    if((a/10)%10==4)cout<<"quad";else
    if((a/10)%10==5)cout<<"pent";else
    if((a/10)%10==6)cout<<"hex" ;else
    if((a/10)%10==7)cout<<"sept";else
    if((a/10)%10==8)cout<<"oct" ;else
    if((a/10)%10==9&&a%10!=0)cout<<"enn" ;else
    if((a/10)%10==9&&a%10==0)cout<<"en"  ;//第二位的暴力
    
    if(a%10==0)cout<<"nil" ;else
    if(a%10==1)cout<<"un"  ;else
    if(a%10==2)cout<<"b"   ;else
    if(a%10==3)cout<<"tr"  ;else
    if(a%10==4)cout<<"quad";else
    if(a%10==5)cout<<"pent";else
    if(a%10==6)cout<<"hex" ;else
    if(a%10==7)cout<<"sept";else
    if(a%10==8)cout<<"oct" ;else
    if(a%10==9)cout<<"enn" ;//第三位的暴力
    
    cout<<"ium"<<endl;//岛国的题必须换行！！！切记！！！
    return 0;
}
```
然后就AC了岛国的这道题。

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

这道题其实也就是个暴力，注意坑即可。

我们枚举原子序数的每一位，然后再根据那个转换表进行转换，再根据题目给出来的坑进行特判：

    有几个需要注意的地方：

    1.首字母大写，要在词尾加-ium（具体为什么貌似是规定）

    2.当尾数是2(-bi)或3(-tri)的时候，因词尾的字母“i”与-ium最前方的“i”重复，故其中的“i”应省略不写。

    3.当9(-enn）后面接的是0(-nil)时，应省略三个n中的一个，只写两个。
    
思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
string s;
int main()
{
	cin>>s;//读入
   //枚举第一位
	if(s[0]=='0')cout<<"Nil";
	if(s[0]=='1')cout<<"Un";
	if(s[0]=='2')cout<<"Bi";
	if(s[0]=='3')cout<<"Tri";
	if(s[0]=='4')cout<<"Quad";
	if(s[0]=='5')cout<<"Pent";
	if(s[0]=='6')cout<<"Hex";
	if(s[0]=='7')cout<<"Sept";
	if(s[0]=='8')cout<<"Oct";
	if(s[0]=='9')cout<<"Enn";
	if(s[1]=='0'&&s[0]!='9')cout<<"nil";
	else if(s[1]=='0'&&s[0]=='9')cout<<"il";//坑
	else//枚举第二位
	{
		if(s[1]=='0')cout<<"nil";
		if(s[1]=='1')cout<<"un";
		if(s[1]=='2')cout<<"bi";
		if(s[1]=='3')cout<<"tri";
		if(s[1]=='4')cout<<"quad";
		if(s[1]=='5')cout<<"pent";
		if(s[1]=='6')cout<<"hex";
		if(s[1]=='7')cout<<"sept";
		if(s[1]=='8')cout<<"oct";
		if(s[1]=='9')cout<<"enn";
	}
	if(s[2]=='0'&&s[1]!='9')cout<<"nil";
	else if(s[2]=='0'&&s[1]=='9')cout<<"il";//坑
	else//枚举第三位
	{
		if(s[2]=='0')cout<<"nil";
		if(s[2]=='1')cout<<"un";
		if(s[2]=='2')cout<<"bi";
		if(s[2]=='3')cout<<"tri";
		if(s[2]=='4')cout<<"quad";
		if(s[2]=='5')cout<<"pent";
		if(s[2]=='6')cout<<"hex";
		if(s[2]=='7')cout<<"sept";
		if(s[2]=='8')cout<<"oct";
		if(s[2]=='9')cout<<"enn";		
	}
	if(s[2]=='2'||s[2]=='3')cout<<"um";//坑
	else cout<<"ium";
	cout<<endl;//记得换行
	return 0;
}
```

好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：Keep_RAD (赞：0)

这一题可以用暴力~~因为正解就是暴力~~。

思路：把输入的三位数拆分成三个字符，输入完一个一个字符进行判断，先处理首字母大写，遇到0看上一个是不是9（第一个除外），特判一次；最后一个字符是2或3就输出`um`，否则输出`ium`。

思想精髓：分数字，分情况处理。
代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[3];//存储三位数
bool flag=0;//判断是不是在处理第一个数
int main()
{
    scanf("%c%c%c",&a[0],&a[1],&a[2]);
    for(int i=0;i<3;i++)//一个一个判断
    {
        if(!flag)//等同于flag==0，用来判断是不是处理第一个数
        {
            flag=1;//标记第一个已经处理过了，避免重复
            if(a[i]=='0') cout<<"Nil";
            if(a[i]=='1') cout<<"Un";
            if(a[i]=='2') cout<<"Bi";
            if(a[i]=='3') cout<<"Tri";
            if(a[i]=='4') cout<<"Quad";
            if(a[i]=='5') cout<<"Pent";
            if(a[i]=='6') cout<<"Hex";
            if(a[i]=='7') cout<<"Sept";
            if(a[i]=='8') cout<<"Oct";
            if(a[i]=='9') cout<<"Enn";//处理每个数字，第一个字符要大写
            continue;//继续到第二个数字
        }
        else//不是第一个数字
        {
            if(a[i]=='0') //特判0
            {
                if(a[i-1]=='9') //如果上一个是9，省略n
                    cout<<"il";
                else //如果不是，正常输出
                    cout<<"nil";
            }
            if(a[i]=='1') cout<<"un";
            if(a[i]=='2') cout<<"bi";
            if(a[i]=='3') cout<<"tri";
            if(a[i]=='4') cout<<"quad";
            if(a[i]=='5') cout<<"pent";
            if(a[i]=='6') cout<<"hex";
            if(a[i]=='7') cout<<"sept";
            if(a[i]=='8') cout<<"oct";
            if(a[i]=='9') cout<<"enn";//继续判断
        }
    }
    if(a[2]=='2' || a[2]=='3') cout<<"um\n";//特判最后一个是不是2或3，如果是就省略i，不是就正常输出
    else cout<<"ium\n";
    return 0;
}

```
bug欢迎指出~~~

Goodbye!

---

## 作者：efgh123 (赞：0)

## 题目
其实就是写一个程序，给你原子序数，叫你来写出元素的名称。

下面是原子序数的每一位数字所代表的词根：（这里直接简写了）

0->nil 1->un

2->bi 3->tri

4->quad 5->pent

6->hex 7->sept

8->oct 9->enn

有几个需要注意的地方：

1.首字母大写，要在词尾加-ium（具体为什么貌似是规定）

2.当尾数是2(-bi)或3(-tri)的时候，因词尾的字母“i”与-ium最前方的“i”重复，故其中的“i”应省略不写。

3.当9(-enn）后面接的是0(-nil)时，应省略三个n中的一个，只写两个。

输入输出：

输入：一个数字N，表示该元素的原子序数。

输出：一行，表示该元素的元素名称

数据范围是117≤N≤999
## 方法
歪解——打表

全部情况（117-999）
```cpp
Ununseptium   Ununoctium   Ununennium   Unbinilium   Unbiunium   
UnbibiumUnbitrium   Unbiquadium   Unbipentium   Unbihexium   Unbiseptium   
UnbioctiumUnbiennium   Untrinilium   Untriunium   Untribium   Untritrium   
UntriquadiumUntripentium   Untrihexium   Untriseptium   Untrioctium   Untriennium   
UnquadniliumUnquadunium   Unquadbium   Unquadtrium   Unquadquadium   Unquadpentium   
UnquadhexiumUnquadseptium   Unquadoctium   Unquadennium   Unpentnilium   Unpentunium   
UnpentbiumUnpenttrium   Unpentquadium   Unpentpentium   Unpenthexium   Unpentseptium   
UnpentoctiumUnpentennium   Unhexnilium   Unhexunium   Unhexbium   Unhextrium   
UnhexquadiumUnhexpentium   Unhexhexium   Unhexseptium   Unhexoctium   Unhexennium   
UnseptniliumUnseptunium   Unseptbium   Unsepttrium   Unseptquadium   Unseptpentium   
UnsepthexiumUnseptseptium   Unseptoctium   Unseptennium   Unoctnilium   Unoctunium   
UnoctbiumUnocttrium   Unoctquadium   Unoctpentium   Unocthexium   Unoctseptium   
UnoctoctiumUnoctennium   Unennilium   Unennunium   Unennbium   Unenntrium   
UnennquadiumUnennpentium   Unennhexium   Unennseptium   Unennoctium   Unennennium   
BinilniliumBinilunium   Binilbium   Biniltrium   Binilquadium   Binilpentium   
BinilhexiumBinilseptium   Biniloctium   Binilennium   Biunnilium   Biununium   
BiunbiumBiuntrium   Biunquadium   Biunpentium   Biunhexium   Biunseptium   
BiunoctiumBiunennium   Bibinilium   Bibiunium   Bibibium   Bibitrium   
BibiquadiumBibipentium   Bibihexium   Bibiseptium   Bibioctium   Bibiennium   
BitriniliumBitriunium   Bitribium   Bitritrium   Bitriquadium   Bitripentium   
BitrihexiumBitriseptium   Bitrioctium   Bitriennium   Biquadnilium   Biquadunium   
BiquadbiumBiquadtrium   Biquadquadium   Biquadpentium   Biquadhexium   Biquadseptium   
BiquadoctiumBiquadennium   Bipentnilium   Bipentunium   Bipentbium   Bipenttrium   
BipentquadiumBipentpentium   Bipenthexium   Bipentseptium   Bipentoctium   Bipentennium   
BihexniliumBihexunium   Bihexbium   Bihextrium   Bihexquadium   Bihexpentium   
BihexhexiumBihexseptium   Bihexoctium   Bihexennium   Biseptnilium   Biseptunium   
BiseptbiumBisepttrium   Biseptquadium   Biseptpentium   Bisepthexium   Biseptseptium   
BiseptoctiumBiseptennium   Bioctnilium   Bioctunium   Bioctbium   Biocttrium   
BioctquadiumBioctpentium   Biocthexium   Bioctseptium   Bioctoctium   Bioctennium   
BienniliumBiennunium   Biennbium   Bienntrium   Biennquadium   Biennpentium   
BiennhexiumBiennseptium   Biennoctium   Biennennium   Trinilnilium   Trinilunium   
TrinilbiumTriniltrium   Trinilquadium   Trinilpentium   Trinilhexium   Trinilseptium   
TriniloctiumTrinilennium   Triunnilium   Triununium   Triunbium   Triuntrium   
TriunquadiumTriunpentium   Triunhexium   Triunseptium   Triunoctium   Triunennium   
TribiniliumTribiunium   Tribibium   Tribitrium   Tribiquadium   Tribipentium   
TribihexiumTribiseptium   Tribioctium   Tribiennium   Tritrinilium   Tritriunium   
TritribiumTritritrium   Tritriquadium   Tritripentium   Tritrihexium   Tritriseptium   
TritrioctiumTritriennium   Triquadnilium   Triquadunium   Triquadbium   Triquadtrium   
TriquadquadiumTriquadpentium   Triquadhexium   Triquadseptium   Triquadoctium   Triquadennium   
TripentniliumTripentunium   Tripentbium   Tripenttrium   Tripentquadium   Tripentpentium   
TripenthexiumTripentseptium   Tripentoctium   Tripentennium   Trihexnilium   Trihexunium   
TrihexbiumTrihextrium   Trihexquadium   Trihexpentium   Trihexhexium   Trihexseptium   
TrihexoctiumTrihexennium   Triseptnilium   Triseptunium   Triseptbium   Trisepttrium   
TriseptquadiumTriseptpentium   Trisepthexium   Triseptseptium   Triseptoctium   Triseptennium   
TrioctniliumTrioctunium   Trioctbium   Triocttrium   Trioctquadium   Trioctpentium   
TriocthexiumTrioctseptium   Trioctoctium   Trioctennium   Triennilium   Triennunium   
TriennbiumTrienntrium   Triennquadium   Triennpentium   Triennhexium   Triennseptium   
TriennoctiumTriennennium   Quadnilnilium   Quadnilunium   Quadnilbium   Quadniltrium   
QuadnilquadiumQuadnilpentium   Quadnilhexium   Quadnilseptium   Quadniloctium   Quadnilennium   
QuadunniliumQuadununium   Quadunbium   Quaduntrium   Quadunquadium   Quadunpentium   
QuadunhexiumQuadunseptium   Quadunoctium   Quadunennium   Quadbinilium   Quadbiunium   
QuadbibiumQuadbitrium   Quadbiquadium   Quadbipentium   Quadbihexium   Quadbiseptium   
QuadbioctiumQuadbiennium   Quadtrinilium   Quadtriunium   Quadtribium   Quadtritrium   
QuadtriquadiumQuadtripentium   Quadtrihexium   Quadtriseptium   Quadtrioctium   Quadtriennium   
QuadquadniliumQuadquadunium   Quadquadbium   Quadquadtrium   Quadquadquadium   Quadquadpentium   
QuadquadhexiumQuadquadseptium   Quadquadoctium   Quadquadennium   Quadpentnilium   Quadpentunium   
QuadpentbiumQuadpenttrium   Quadpentquadium   Quadpentpentium   Quadpenthexium   Quadpentseptium   
QuadpentoctiumQuadpentennium   Quadhexnilium   Quadhexunium   Quadhexbium   Quadhextrium   
QuadhexquadiumQuadhexpentium   Quadhexhexium   Quadhexseptium   Quadhexoctium   Quadhexennium   
QuadseptniliumQuadseptunium   Quadseptbium   Quadsepttrium   Quadseptquadium   Quadseptpentium   
QuadsepthexiumQuadseptseptium   Quadseptoctium   Quadseptennium   Quadoctnilium   Quadoctunium   
QuadoctbiumQuadocttrium   Quadoctquadium   Quadoctpentium   Quadocthexium   Quadoctseptium   
QuadoctoctiumQuadoctennium   Quadennilium   Quadennunium   Quadennbium   Quadenntrium   
QuadennquadiumQuadennpentium   Quadennhexium   Quadennseptium   Quadennoctium   Quadennennium   
PentnilniliumPentnilunium   Pentnilbium   Pentniltrium   Pentnilquadium   Pentnilpentium   
PentnilhexiumPentnilseptium   Pentniloctium   Pentnilennium   Pentunnilium   Pentununium   
PentunbiumPentuntrium   Pentunquadium   Pentunpentium   Pentunhexium   Pentunseptium   
PentunoctiumPentunennium   Pentbinilium   Pentbiunium   Pentbibium   Pentbitrium   
PentbiquadiumPentbipentium   Pentbihexium   Pentbiseptium   Pentbioctium   Pentbiennium   
PenttriniliumPenttriunium   Penttribium   Penttritrium   Penttriquadium   Penttripentium   
PenttrihexiumPenttriseptium   Penttrioctium   Penttriennium   Pentquadnilium   Pentquadunium   
PentquadbiumPentquadtrium   Pentquadquadium   Pentquadpentium   Pentquadhexium   Pentquadseptium   
PentquadoctiumPentquadennium   Pentpentnilium   Pentpentunium   Pentpentbium   Pentpenttrium   
PentpentquadiumPentpentpentium   Pentpenthexium   Pentpentseptium   Pentpentoctium   Pentpentennium   
PenthexniliumPenthexunium   Penthexbium   Penthextrium   Penthexquadium   Penthexpentium   
PenthexhexiumPenthexseptium   Penthexoctium   Penthexennium   Pentseptnilium   Pentseptunium   
PentseptbiumPentsepttrium   Pentseptquadium   Pentseptpentium   Pentsepthexium   Pentseptseptium   
PentseptoctiumPentseptennium   Pentoctnilium   Pentoctunium   Pentoctbium   Pentocttrium   
PentoctquadiumPentoctpentium   Pentocthexium   Pentoctseptium   Pentoctoctium   Pentoctennium   
PentenniliumPentennunium   Pentennbium   Pentenntrium   Pentennquadium   Pentennpentium   
PentennhexiumPentennseptium   Pentennoctium   Pentennennium   Hexnilnilium   Hexnilunium   
HexnilbiumHexniltrium   Hexnilquadium   Hexnilpentium   Hexnilhexium   Hexnilseptium   
HexniloctiumHexnilennium   Hexunnilium   Hexununium   Hexunbium   Hexuntrium   
HexunquadiumHexunpentium   Hexunhexium   Hexunseptium   Hexunoctium   Hexunennium   
HexbiniliumHexbiunium   Hexbibium   Hexbitrium   Hexbiquadium   Hexbipentium   
HexbihexiumHexbiseptium   Hexbioctium   Hexbiennium   Hextrinilium   Hextriunium   
HextribiumHextritrium   Hextriquadium   Hextripentium   Hextrihexium   Hextriseptium   
HextrioctiumHextriennium   Hexquadnilium   Hexquadunium   Hexquadbium   Hexquadtrium   
HexquadquadiumHexquadpentium   Hexquadhexium   Hexquadseptium   Hexquadoctium   Hexquadennium   
HexpentniliumHexpentunium   Hexpentbium   Hexpenttrium   Hexpentquadium   Hexpentpentium   
HexpenthexiumHexpentseptium   Hexpentoctium   Hexpentennium   Hexhexnilium   Hexhexunium   
HexhexbiumHexhextrium   Hexhexquadium   Hexhexpentium   Hexhexhexium   Hexhexseptium   
HexhexoctiumHexhexennium   Hexseptnilium   Hexseptunium   Hexseptbium   Hexsepttrium   
HexseptquadiumHexseptpentium   Hexsepthexium   Hexseptseptium   Hexseptoctium   Hexseptennium   
HexoctniliumHexoctunium   Hexoctbium   Hexocttrium   Hexoctquadium   Hexoctpentium   
HexocthexiumHexoctseptium   Hexoctoctium   Hexoctennium   Hexennilium   Hexennunium   
HexennbiumHexenntrium   Hexennquadium   Hexennpentium   Hexennhexium   Hexennseptium   
HexennoctiumHexennennium   Septnilnilium   Septnilunium   Septnilbium   Septniltrium   
SeptnilquadiumSeptnilpentium   Septnilhexium   Septnilseptium   Septniloctium   Septnilennium   
SeptunniliumSeptununium   Septunbium   Septuntrium   Septunquadium   Septunpentium   
SeptunhexiumSeptunseptium   Septunoctium   Septunennium   Septbinilium   Septbiunium   
SeptbibiumSeptbitrium   Septbiquadium   Septbipentium   Septbihexium   Septbiseptium   
SeptbioctiumSeptbiennium   Septtrinilium   Septtriunium   Septtribium   Septtritrium   
SepttriquadiumSepttripentium   Septtrihexium   Septtriseptium   Septtrioctium   Septtriennium   
SeptquadniliumSeptquadunium   Septquadbium   Septquadtrium   Septquadquadium   Septquadpentium   
SeptquadhexiumSeptquadseptium   Septquadoctium   Septquadennium   Septpentnilium   Septpentunium   
SeptpentbiumSeptpenttrium   Septpentquadium   Septpentpentium   Septpenthexium   Septpentseptium   
SeptpentoctiumSeptpentennium   Septhexnilium   Septhexunium   Septhexbium   Septhextrium   
SepthexquadiumSepthexpentium   Septhexhexium   Septhexseptium   Septhexoctium   Septhexennium   
SeptseptniliumSeptseptunium   Septseptbium   Septsepttrium   Septseptquadium   Septseptpentium   
SeptsepthexiumSeptseptseptium   Septseptoctium   Septseptennium   Septoctnilium   Septoctunium   
SeptoctbiumSeptocttrium   Septoctquadium   Septoctpentium   Septocthexium   Septoctseptium   
SeptoctoctiumSeptoctennium   Septennilium   Septennunium   Septennbium   Septenntrium   
SeptennquadiumSeptennpentium   Septennhexium   Septennseptium   Septennoctium   Septennennium   
OctnilniliumOctnilunium   Octnilbium   Octniltrium   Octnilquadium   Octnilpentium   
OctnilhexiumOctnilseptium   Octniloctium   Octnilennium   Octunnilium   Octununium   
OctunbiumOctuntrium   Octunquadium   Octunpentium   Octunhexium   Octunseptium   
OctunoctiumOctunennium   Octbinilium   Octbiunium   Octbibium   Octbitrium   
OctbiquadiumOctbipentium   Octbihexium   Octbiseptium   Octbioctium   Octbiennium   
OcttriniliumOcttriunium   Octtribium   Octtritrium   Octtriquadium   Octtripentium   
OcttrihexiumOcttriseptium   Octtrioctium   Octtriennium   Octquadnilium   Octquadunium   
OctquadbiumOctquadtrium   Octquadquadium   Octquadpentium   Octquadhexium   Octquadseptium   
OctquadoctiumOctquadennium   Octpentnilium   Octpentunium   Octpentbium   Octpenttrium   
OctpentquadiumOctpentpentium   Octpenthexium   Octpentseptium   Octpentoctium   Octpentennium   
OcthexniliumOcthexunium   Octhexbium   Octhextrium   Octhexquadium   Octhexpentium   
OcthexhexiumOcthexseptium   Octhexoctium   Octhexennium   Octseptnilium   Octseptunium   
OctseptbiumOctsepttrium   Octseptquadium   Octseptpentium   Octsepthexium   Octseptseptium   
OctseptoctiumOctseptennium   Octoctnilium   Octoctunium   Octoctbium   Octocttrium   
OctoctquadiumOctoctpentium   Octocthexium   Octoctseptium   Octoctoctium   Octoctennium   
OctenniliumOctennunium   Octennbium   Octenntrium   Octennquadium   Octennpentium   
OctennhexiumOctennseptium   Octennoctium   Octennennium   Ennilnilium   Ennilunium   
EnnilbiumEnniltrium   Ennilquadium   Ennilpentium   Ennilhexium   Ennilseptium   
EnniloctiumEnnilennium   Ennunnilium   Ennununium   Ennunbium   Ennuntrium   
EnnunquadiumEnnunpentium   Ennunhexium   Ennunseptium   Ennunoctium   Ennunennium   
EnnbiniliumEnnbiunium   Ennbibium   Ennbitrium   Ennbiquadium   Ennbipentium   
EnnbihexiumEnnbiseptium   Ennbioctium   Ennbiennium   Enntrinilium   Enntriunium   
EnntribiumEnntritrium   Enntriquadium   Enntripentium   Enntrihexium   Enntriseptium   
EnntrioctiumEnntriennium   Ennquadnilium   Ennquadunium   Ennquadbium   Ennquadtrium   
EnnquadquadiumEnnquadpentium   Ennquadhexium   Ennquadseptium   Ennquadoctium   Ennquadennium   
EnnpentniliumEnnpentunium   Ennpentbium   Ennpenttrium   Ennpentquadium   Ennpentpentium   
EnnpenthexiumEnnpentseptium   Ennpentoctium   Ennpentennium   Ennhexnilium   Ennhexunium   
EnnhexbiumEnnhextrium   Ennhexquadium   Ennhexpentium   Ennhexhexium   Ennhexseptium   
EnnhexoctiumEnnhexennium   Ennseptnilium   Ennseptunium   Ennseptbium   Ennsepttrium   
EnnseptquadiumEnnseptpentium   Ennsepthexium   Ennseptseptium   Ennseptoctium   Ennseptennium   
EnnoctniliumEnnoctunium   Ennoctbium   Ennocttrium   Ennoctquadium   Ennoctpentium   
EnnocthexiumEnnoctseptium   Ennoctoctium   Ennoctennium   Ennennilium   Ennennunium   
EnnennbiumEnnenntrium   Ennennquadium   Ennennpentium   Ennennhexium   Ennennseptium   
EnnennoctiumEnnennennium   
```
代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string ans[999]={" "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ","Ununseptium","Ununoctium","Ununennium","Unbinilium","Unbiunium","Unbibium","Unbitrium","Unbiquadium","Unbipentium","Unbihexium","Unbiseptium","Unbioctium","Unbiennium","Untrinilium","Untriunium","Untribium","Untritrium","Untriquadium","Untripentium","Untrihexium","Untriseptium","Untrioctium","Untriennium","Unquadnilium","Unquadunium","Unquadbium","Unquadtrium","Unquadquadium","Unquadpentium","Unquadhexium","Unquadseptium","Unquadoctium","Unquadennium","Unpentnilium","Unpentunium","Unpentbium","Unpenttrium","Unpentquadium","Unpentpentium","Unpenthexium","Unpentseptium","Unpentoctium","Unpentennium","Unhexnilium","Unhexunium","Unhexbium","Unhextrium","Unhexquadium","Unhexpentium","Unhexhexium","Unhexseptium","Unhexoctium","Unhexennium","Unseptnilium","Unseptunium","Unseptbium","Unsepttrium","Unseptquadium","Unseptpentium","Unsepthexium","Unseptseptium","Unseptoctium","Unseptennium","Unoctnilium","Unoctunium","Unoctbium","Unocttrium","Unoctquadium","Unoctpentium","Unocthexium","Unoctseptium","Unoctoctium","Unoctennium","Unennilium","Unennunium","Unennbium","Unenntrium","Unennquadium","Unennpentium","Unennhexium","Unennseptium","Unennoctium","Unennennium","Binilnilium","Binilunium","Binilbium","Biniltrium","Binilquadium","Binilpentium","Binilhexium","Binilseptium","Biniloctium","Binilennium","Biunnilium","Biununium","Biunbium","Biuntrium","Biunquadium","Biunpentium","Biunhexium","Biunseptium","Biunoctium","Biunennium","Bibinilium","Bibiunium","Bibibium","Bibitrium","Bibiquadium","Bibipentium","Bibihexium","Bibiseptium","Bibioctium","Bibiennium","Bitrinilium","Bitriunium","Bitribium","Bitritrium","Bitriquadium","Bitripentium","Bitrihexium","Bitriseptium","Bitrioctium","Bitriennium","Biquadnilium","Biquadunium","Biquadbium","Biquadtrium","Biquadquadium","Biquadpentium","Biquadhexium","Biquadseptium","Biquadoctium","Biquadennium","Bipentnilium","Bipentunium","Bipentbium","Bipenttrium","Bipentquadium","Bipentpentium","Bipenthexium","Bipentseptium","Bipentoctium","Bipentennium","Bihexnilium","Bihexunium","Bihexbium","Bihextrium","Bihexquadium","Bihexpentium","Bihexhexium","Bihexseptium","Bihexoctium","Bihexennium","Biseptnilium","Biseptunium","Biseptbium","Bisepttrium","Biseptquadium","Biseptpentium","Bisepthexium","Biseptseptium","Biseptoctium","Biseptennium","Bioctnilium","Bioctunium","Bioctbium","Biocttrium","Bioctquadium","Bioctpentium","Biocthexium","Bioctseptium","Bioctoctium","Bioctennium","Biennilium","Biennunium","Biennbium","Bienntrium","Biennquadium","Biennpentium","Biennhexium","Biennseptium","Biennoctium","Biennennium","Trinilnilium","Trinilunium","Trinilbium","Triniltrium","Trinilquadium","Trinilpentium","Trinilhexium","Trinilseptium","Triniloctium","Trinilennium","Triunnilium","Triununium","Triunbium","Triuntrium","Triunquadium","Triunpentium","Triunhexium","Triunseptium","Triunoctium","Triunennium","Tribinilium","Tribiunium","Tribibium","Tribitrium","Tribiquadium","Tribipentium","Tribihexium","Tribiseptium","Tribioctium","Tribiennium","Tritrinilium","Tritriunium","Tritribium","Tritritrium","Tritriquadium","Tritripentium","Tritrihexium","Tritriseptium","Tritrioctium","Tritriennium","Triquadnilium","Triquadunium","Triquadbium","Triquadtrium","Triquadquadium","Triquadpentium","Triquadhexium","Triquadseptium","Triquadoctium","Triquadennium","Tripentnilium","Tripentunium","Tripentbium","Tripenttrium","Tripentquadium","Tripentpentium","Tripenthexium","Tripentseptium","Tripentoctium","Tripentennium","Trihexnilium","Trihexunium","Trihexbium","Trihextrium","Trihexquadium","Trihexpentium","Trihexhexium","Trihexseptium","Trihexoctium","Trihexennium","Triseptnilium","Triseptunium","Triseptbium","Trisepttrium","Triseptquadium","Triseptpentium","Trisepthexium","Triseptseptium","Triseptoctium","Triseptennium","Trioctnilium","Trioctunium","Trioctbium","Triocttrium","Trioctquadium","Trioctpentium","Triocthexium","Trioctseptium","Trioctoctium","Trioctennium","Triennilium","Triennunium","Triennbium","Trienntrium","Triennquadium","Triennpentium","Triennhexium","Triennseptium","Triennoctium","Triennennium","Quadnilnilium","Quadnilunium","Quadnilbium","Quadniltrium","Quadnilquadium","Quadnilpentium","Quadnilhexium","Quadnilseptium","Quadniloctium","Quadnilennium","Quadunnilium","Quadununium","Quadunbium","Quaduntrium","Quadunquadium","Quadunpentium","Quadunhexium","Quadunseptium","Quadunoctium","Quadunennium","Quadbinilium","Quadbiunium","Quadbibium","Quadbitrium","Quadbiquadium","Quadbipentium","Quadbihexium","Quadbiseptium","Quadbioctium","Quadbiennium","Quadtrinilium","Quadtriunium","Quadtribium","Quadtritrium","Quadtriquadium","Quadtripentium","Quadtrihexium","Quadtriseptium","Quadtrioctium","Quadtriennium","Quadquadnilium","Quadquadunium","Quadquadbium","Quadquadtrium","Quadquadquadium","Quadquadpentium","Quadquadhexium","Quadquadseptium","Quadquadoctium","Quadquadennium","Quadpentnilium","Quadpentunium","Quadpentbium","Quadpenttrium","Quadpentquadium","Quadpentpentium","Quadpenthexium","Quadpentseptium","Quadpentoctium","Quadpentennium","Quadhexnilium","Quadhexunium","Quadhexbium","Quadhextrium","Quadhexquadium","Quadhexpentium","Quadhexhexium","Quadhexseptium","Quadhexoctium","Quadhexennium","Quadseptnilium","Quadseptunium","Quadseptbium","Quadsepttrium","Quadseptquadium","Quadseptpentium","Quadsepthexium","Quadseptseptium","Quadseptoctium","Quadseptennium","Quadoctnilium","Quadoctunium","Quadoctbium","Quadocttrium","Quadoctquadium","Quadoctpentium","Quadocthexium","Quadoctseptium","Quadoctoctium","Quadoctennium","Quadennilium","Quadennunium","Quadennbium","Quadenntrium","Quadennquadium","Quadennpentium","Quadennhexium","Quadennseptium","Quadennoctium","Quadennennium","Pentnilnilium","Pentnilunium","Pentnilbium","Pentniltrium","Pentnilquadium","Pentnilpentium","Pentnilhexium","Pentnilseptium","Pentniloctium","Pentnilennium","Pentunnilium","Pentununium","Pentunbium","Pentuntrium","Pentunquadium","Pentunpentium","Pentunhexium","Pentunseptium","Pentunoctium","Pentunennium","Pentbinilium","Pentbiunium","Pentbibium","Pentbitrium","Pentbiquadium","Pentbipentium","Pentbihexium","Pentbiseptium","Pentbioctium","Pentbiennium","Penttrinilium","Penttriunium","Penttribium","Penttritrium","Penttriquadium","Penttripentium","Penttrihexium","Penttriseptium","Penttrioctium","Penttriennium","Pentquadnilium","Pentquadunium","Pentquadbium","Pentquadtrium","Pentquadquadium","Pentquadpentium","Pentquadhexium","Pentquadseptium","Pentquadoctium","Pentquadennium","Pentpentnilium","Pentpentunium","Pentpentbium","Pentpenttrium","Pentpentquadium","Pentpentpentium","Pentpenthexium","Pentpentseptium","Pentpentoctium","Pentpentennium","Penthexnilium","Penthexunium","Penthexbium","Penthextrium","Penthexquadium","Penthexpentium","Penthexhexium","Penthexseptium","Penthexoctium","Penthexennium","Pentseptnilium","Pentseptunium","Pentseptbium","Pentsepttrium","Pentseptquadium","Pentseptpentium","Pentsepthexium","Pentseptseptium","Pentseptoctium","Pentseptennium","Pentoctnilium","Pentoctunium","Pentoctbium","Pentocttrium","Pentoctquadium","Pentoctpentium","Pentocthexium","Pentoctseptium","Pentoctoctium","Pentoctennium","Pentennilium","Pentennunium","Pentennbium","Pentenntrium","Pentennquadium","Pentennpentium","Pentennhexium","Pentennseptium","Pentennoctium","Pentennennium","Hexnilnilium","Hexnilunium","Hexnilbium","Hexniltrium","Hexnilquadium","Hexnilpentium","Hexnilhexium","Hexnilseptium","Hexniloctium","Hexnilennium","Hexunnilium","Hexununium","Hexunbium","Hexuntrium","Hexunquadium","Hexunpentium","Hexunhexium","Hexunseptium","Hexunoctium","Hexunennium","Hexbinilium","Hexbiunium","Hexbibium","Hexbitrium","Hexbiquadium","Hexbipentium","Hexbihexium","Hexbiseptium","Hexbioctium","Hexbiennium","Hextrinilium","Hextriunium","Hextribium","Hextritrium","Hextriquadium","Hextripentium","Hextrihexium","Hextriseptium","Hextrioctium","Hextriennium","Hexquadnilium","Hexquadunium","Hexquadbium","Hexquadtrium","Hexquadquadium","Hexquadpentium","Hexquadhexium","Hexquadseptium","Hexquadoctium","Hexquadennium","Hexpentnilium","Hexpentunium","Hexpentbium","Hexpenttrium","Hexpentquadium","Hexpentpentium","Hexpenthexium","Hexpentseptium","Hexpentoctium","Hexpentennium","Hexhexnilium","Hexhexunium","Hexhexbium","Hexhextrium","Hexhexquadium","Hexhexpentium","Hexhexhexium","Hexhexseptium","Hexhexoctium","Hexhexennium","Hexseptnilium","Hexseptunium","Hexseptbium","Hexsepttrium","Hexseptquadium","Hexseptpentium","Hexsepthexium","Hexseptseptium","Hexseptoctium","Hexseptennium","Hexoctnilium","Hexoctunium","Hexoctbium","Hexocttrium","Hexoctquadium","Hexoctpentium","Hexocthexium","Hexoctseptium","Hexoctoctium","Hexoctennium","Hexennilium","Hexennunium","Hexennbium","Hexenntrium","Hexennquadium","Hexennpentium","Hexennhexium","Hexennseptium","Hexennoctium","Hexennennium","Septnilnilium","Septnilunium","Septnilbium","Septniltrium","Septnilquadium","Septnilpentium","Septnilhexium","Septnilseptium","Septniloctium","Septnilennium","Septunnilium","Septununium","Septunbium","Septuntrium","Septunquadium","Septunpentium","Septunhexium","Septunseptium","Septunoctium","Septunennium","Septbinilium","Septbiunium","Septbibium","Septbitrium","Septbiquadium","Septbipentium","Septbihexium","Septbiseptium","Septbioctium","Septbiennium","Septtrinilium","Septtriunium","Septtribium","Septtritrium","Septtriquadium","Septtripentium","Septtrihexium","Septtriseptium","Septtrioctium","Septtriennium","Septquadnilium","Septquadunium","Septquadbium","Septquadtrium","Septquadquadium","Septquadpentium","Septquadhexium","Septquadseptium","Septquadoctium","Septquadennium","Septpentnilium","Septpentunium","Septpentbium","Septpenttrium","Septpentquadium","Septpentpentium","Septpenthexium","Septpentseptium","Septpentoctium","Septpentennium","Septhexnilium","Septhexunium","Septhexbium","Septhextrium","Septhexquadium","Septhexpentium","Septhexhexium","Septhexseptium","Septhexoctium","Septhexennium","Septseptnilium","Septseptunium","Septseptbium","Septsepttrium","Septseptquadium","Septseptpentium","Septsepthexium","Septseptseptium","Septseptoctium","Septseptennium","Septoctnilium","Septoctunium","Septoctbium","Septocttrium","Septoctquadium","Septoctpentium","Septocthexium","Septoctseptium","Septoctoctium","Septoctennium","Septennilium","Septennunium","Septennbium","Septenntrium","Septennquadium","Septennpentium","Septennhexium","Septennseptium","Septennoctium","Septennennium","Octnilnilium","Octnilunium","Octnilbium","Octniltrium","Octnilquadium","Octnilpentium","Octnilhexium","Octnilseptium","Octniloctium","Octnilennium","Octunnilium","Octununium","Octunbium","Octuntrium","Octunquadium","Octunpentium","Octunhexium","Octunseptium","Octunoctium","Octunennium","Octbinilium","Octbiunium","Octbibium","Octbitrium","Octbiquadium","Octbipentium","Octbihexium","Octbiseptium","Octbioctium","Octbiennium","Octtrinilium","Octtriunium","Octtribium","Octtritrium","Octtriquadium","Octtripentium","Octtrihexium","Octtriseptium","Octtrioctium","Octtriennium","Octquadnilium","Octquadunium","Octquadbium","Octquadtrium","Octquadquadium","Octquadpentium","Octquadhexium","Octquadseptium","Octquadoctium","Octquadennium","Octpentnilium","Octpentunium","Octpentbium","Octpenttrium","Octpentquadium","Octpentpentium","Octpenthexium","Octpentseptium","Octpentoctium","Octpentennium","Octhexnilium","Octhexunium","Octhexbium","Octhextrium","Octhexquadium","Octhexpentium","Octhexhexium","Octhexseptium","Octhexoctium","Octhexennium","Octseptnilium","Octseptunium","Octseptbium","Octsepttrium","Octseptquadium","Octseptpentium","Octsepthexium","Octseptseptium","Octseptoctium","Octseptennium","Octoctnilium","Octoctunium","Octoctbium","Octocttrium","Octoctquadium","Octoctpentium","Octocthexium","Octoctseptium","Octoctoctium","Octoctennium","Octennilium","Octennunium","Octennbium","Octenntrium","Octennquadium","Octennpentium","Octennhexium","Octennseptium","Octennoctium","Octennennium","Ennilnilium","Ennilunium","Ennilbium","Enniltrium","Ennilquadium","Ennilpentium","Ennilhexium","Ennilseptium","Enniloctium","Ennilennium","Ennunnilium","Ennununium","Ennunbium","Ennuntrium","Ennunquadium","Ennunpentium","Ennunhexium","Ennunseptium","Ennunoctium","Ennunennium","Ennbinilium","Ennbiunium","Ennbibium","Ennbitrium","Ennbiquadium","Ennbipentium","Ennbihexium","Ennbiseptium","Ennbioctium","Ennbiennium","Enntrinilium","Enntriunium","Enntribium","Enntritrium","Enntriquadium","Enntripentium","Enntrihexium","Enntriseptium","Enntrioctium","Enntriennium","Ennquadnilium","Ennquadunium","Ennquadbium","Ennquadtrium","Ennquadquadium","Ennquadpentium","Ennquadhexium","Ennquadseptium","Ennquadoctium","Ennquadennium","Ennpentnilium","Ennpentunium","Ennpentbium","Ennpenttrium","Ennpentquadium","Ennpentpentium","Ennpenthexium","Ennpentseptium","Ennpentoctium","Ennpentennium","Ennhexnilium","Ennhexunium","Ennhexbium","Ennhextrium","Ennhexquadium","Ennhexpentium","Ennhexhexium","Ennhexseptium","Ennhexoctium","Ennhexennium","Ennseptnilium","Ennseptunium","Ennseptbium","Ennsepttrium","Ennseptquadium","Ennseptpentium","Ennsepthexium","Ennseptseptium","Ennseptoctium","Ennseptennium","Ennoctnilium","Ennoctunium","Ennoctbium","Ennocttrium","Ennoctquadium","Ennoctpentium","Ennocthexium","Ennoctseptium","Ennoctoctium","Ennoctennium","Ennennilium","Ennennunium","Ennennbium","Ennenntrium","Ennennquadium","Ennennpentium","Ennennhexium","Ennennseptium","Ennennoctium","Ennennennium"};
int main(){
	int n;
	cin>>n;
	cout<<ans[n-1]<<endl;
    return 0;
}
```
注意：打表是歪解，虽然方便，但不要依赖打表

---

## 作者：听取MLE声一片 (赞：0)

**注意1**：直接枚举判断时，建议压行

好了，这道题是很简单的，只是敲代码比较难

主要思路：把输入n从头到尾顺一遍，然后0~9判定就行了

**注意2**：不能直接加入然后去重，因为9是两个n，再加特判会更加麻烦

**注意3**：题目一定要读全，3个注意落掉一个就完了

**注意4**：n建议用字符串存储，因为数字的大多是从低位到高位而非从高位到低位

**注意5**：0~9的字符一定要敲对，因为这是AT评测，根本查不出来

**注意6**：老生常谈，AT文末换行

**注意7**建议用char存储，用l记录长度（不过直接输出更香）

**注意8**去重不建议删除，建议更改插入就行

好了，下面是代码

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
string n;
int l;
char a[1001];
int main()
{
	cin>>n;
	for(int i=0;i<n.length();i++){
		if(n[i]=='0'){
			if(i>0){
				if(n[i-1]=='9'){
					a[l]='i';
					l++;
					a[l]='l';
					l++;
					continue;
				}
			}
			a[l]='n';
			l++;
			a[l]='i';
			l++;
			a[l]='l';
			l++;
		}
		if(n[i]=='1'){
			a[l]='u';
			l++;
			a[l]='n';
			l++;
		}
		if(n[i]=='2'){
			a[l]='b';
			l++;
			a[l]='i';
			l++;
		}
		if(n[i]=='3'){
			a[l]='t';
			l++;
			a[l]='r';
			l++;
			a[l]='i';
			l++;
		}
		if(n[i]=='4'){
			a[l]='q';
			l++;
			a[l]='u';
			l++;
			a[l]='a';
			l++;
			a[l]='d';
			l++;
		}
		if(n[i]=='5'){
			a[l]='p';
			l++;
			a[l]='e';
			l++;
			a[l]='n';
			l++;
			a[l]='t';
			l++;
		}
		if(n[i]=='6'){
			a[l]='h';
			l++;
			a[l]='e';
			l++;
			a[l]='x';
			l++;
		}
		if(n[i]=='7'){
			a[l]='s';
			l++;
			a[l]='e';
			l++;
			a[l]='p';
			l++;
			a[l]='t';
			l++;
		}
		if(n[i]=='8'){
			a[l]='o';
			l++;
			a[l]='c';
			l++;
			a[l]='t';
			l++;
		}
		if(n[i]=='9'){
			a[l]='e';
			l++;
			a[l]='n';
			l++;
			a[l]='n';
			l++;
		}
	}
	if(n[n.length()-1]=='2'||n[n.length()-1]=='3'){
		a[l]='u';
		l++;
		a[l]='m';
		l++;
	}
	else{	
		a[l]='i';
		l++;
		a[l]='u';
		l++;
		a[l]='m';
		l++;	
	}
	a[0]='A'+a[0]-'a'; 
	for(int i=0;i<l;i++)//顺次输出
		cout<<a[i];
	cout<<endl;
    return 0;
}
```
感谢大家！

---

## 作者：tZEROちゃん (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT859)。

介绍一种使用`string`字符串的方法。
>$string$是$C++$、$java$、$VB$等编程语言中的字符串，字符串是一个特殊的对象，属于引用类型。 $C++$标准库中$string$类以类型的形式对字符串进行封装，且包含了字符序列的处理操作。——百度百科

**思路：**

1. 初步想法：            
我们可以定义一个字符串，然后逐位输出对应的原子序数。

2. 定义一个字符串s，并输入。
```cpp
	string s;
	cin>>s;
```
3. 按照百位->十位->个位的顺序进行判断&输出：先判断百位并输出。
```cpp
	if(s[0]=='0')cout<<"Nil";
	if(s[0]=='1')cout<<"Un"; 
	if(s[0]=='2')cout<<"Bi";
	if(s[0]=='3')cout<<"Tri";
	if(s[0]=='4')cout<<"Quad";
	if(s[0]=='5')cout<<"Pent";
	if(s[0]=='6')cout<<"Hex";
	if(s[0]=='7')cout<<"Sept";
	if(s[0]=='8')cout<<"Oct";
	if(s[0]=='9')cout<<"Enn";
```
4. 判断十位并输出。注意，这里有一些坑点需要注意。
```cpp
	if(s[1]=='0' && s[0]!='9')cout<<"nil";
	if(s[1]=='0' && s[0]=='9')cout<<"il";
	if(s[1]=='1')cout<<"un";
	if(s[1]=='2')cout<<"bi";
	if(s[1]=='3')cout<<"tri";
	if(s[1]=='4')cout<<"quad";
	if(s[1]=='5')cout<<"pent";
	if(s[1]=='6')cout<<"hex";
	if(s[1]=='7')cout<<"sept";
	if(s[1]=='8')cout<<"oct";
	if(s[1]=='9')cout<<"enn";
```
5. 最后判断个位并输出。
```cpp
	if(s[2]=='0' && s[1]!='9')cout<<"nil";
	if(s[2]=='0' && s[1]=='9')cout<<"il";
	if(s[2]=='1')cout<<"un";
	if(s[2]=='2')cout<<"bi";
	if(s[2]=='3')cout<<"tri";
	if(s[2]=='4')cout<<"quad";
	if(s[2]=='5')cout<<"pent";
	if(s[2]=='6')cout<<"hex";
	if(s[2]=='7')cout<<"sept";
	if(s[2]=='8')cout<<"oct";
	if(s[2]=='9')cout<<"enn";
```
6. 输出最后的词尾。这里需要特判一下。
```cpp
	if(s[2]=='2' || s[2]=='3')cout<<"um";
	else cout<<"ium";
```
_________________
**代码实现：**
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	cin>>s;
	//--------百位--------
	if(s[0]=='0')cout<<"Nil";
	if(s[0]=='1')cout<<"Un"; 
	if(s[0]=='2')cout<<"Bi";
	if(s[0]=='3')cout<<"Tri";
	if(s[0]=='4')cout<<"Quad";
	if(s[0]=='5')cout<<"Pent";
	if(s[0]=='6')cout<<"Hex";
	if(s[0]=='7')cout<<"Sept";
	if(s[0]=='8')cout<<"Oct";
	if(s[0]=='9')cout<<"Enn";
	//--------十位--------
	if(s[1]=='0' && s[0]!='9')cout<<"nil";
	if(s[1]=='0' && s[0]=='9')cout<<"il";
	if(s[1]=='1')cout<<"un";
	if(s[1]=='2')cout<<"bi";
	if(s[1]=='3')cout<<"tri";
	if(s[1]=='4')cout<<"quad";
	if(s[1]=='5')cout<<"pent";
	if(s[1]=='6')cout<<"hex";
	if(s[1]=='7')cout<<"sept";
	if(s[1]=='8')cout<<"oct";
	if(s[1]=='9')cout<<"enn";
	//--------个位--------
	if(s[2]=='0' && s[1]!='9')cout<<"nil";
	if(s[2]=='0' && s[1]=='9')cout<<"il";
	if(s[2]=='1')cout<<"un";
	if(s[2]=='2')cout<<"bi";
	if(s[2]=='3')cout<<"tri";
	if(s[2]=='4')cout<<"quad";
	if(s[2]=='5')cout<<"pent";
	if(s[2]=='6')cout<<"hex";
	if(s[2]=='7')cout<<"sept";
	if(s[2]=='8')cout<<"oct";
	if(s[2]=='9')cout<<"enn";
	//--------尾数--------
	if(s[2]=='2' || s[2]=='3')cout<<"um";
	else cout<<"ium";
	return 0;
}
```

---

## 作者：Trans_Portal (赞：0)

本题难度不大，坑点多，坑度堪比[多项式输出](https://www.luogu.org/problem/P1067)。

翻译者给出了所有要注意的点，重视的话应该不会出错。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string a[11]={"nil","un","bi","tri","quad","pent","hex","sept","oct","enn","ium"};//方便输出 
int main(){
	int n,x,y,z;
	cin>>n;
	x=n/100;y=n/10%10;z=n%10;//x百位，y十位，z个位 
	if(z==2||z==3)//2.当尾数是-bi或-tri的时候，因词尾的字母“i”与-ium最前方的“i”重复，故其中的“i”应省略不写。 
		a[10]="um";
	a[x][0]+='A'-'a';//1.首字母大写
	cout<<a[x];
	a[x][0]-='A'-'a';//回溯
	if(x==9&&y==0)//3.当9(-enn）后面接的是0(-nil)时，应省略三个n中的一个，只写两个。 
		cout<<"il"<<a[z]<<a[10]<<endl;//"il"是为了不影响后面的输出，下同 
	else if(y==9&&z==0)
		cout<<a[y]<<"il"<<a[10]<<endl;
	else
		cout<<a[y]<<a[z]<<a[10]<<endl;//正常情况 
}
```
 _个人觉得楼下暴力更简单，看着也舒服。_ 

---

## 作者：gen_Ferrous (赞：0)

#### ~~水题一道，但是模拟很过分。~~

主要思路：一个一个字符输出（雾）。~~用打表的话。。。~~

优化：先打一个小表（0~9的词根），逐一输出。

其实相当于一些判断（特判）。

输入的处理：

	三位数：数位分离会吗？
    
**int aa=n/100,bb=(n/10)%10,cc=n%10;**

这上面是数位分离。

```cpp
#include<cstdio>
char a[12][5]={"nil","un","bi","tri","quad","pent","hex","sept","oct","enn"};//打表？
char b[30];
int c[12]={3,2,2,3,4,4,3,4,3,3};//a数组中每个字符串的长度。
								//鄙人不才，不想用strlen()。
int main(){
	int n,tot=0;
	for(int i=0;i<30;i++) b[i]='\0';
	scanf("%d",&n);
	int aa=n/100,bb=(n/10)%10,cc=n%10;//数位分离，但是用三个变量存储。
	for(int i=0;i<c[aa];++i) {b[tot]=a[aa][i]; tot++;}
	if(aa==9&&bb==0) tot--;//特判：如904的特殊情况。
	b[0]-=32;//这是什么？将首位变成大写。
	for(int i=0;i<c[bb];++i) {b[i+tot]=a[bb][i];}
	if(bb==9&&cc==0) tot--;
	tot+=c[bb];
	for(int i=0;i<c[cc];++i) {b[tot+i]=a[cc][i];}
	if(cc==2 || cc==3) tot--;
	tot+=c[cc];
	b[tot]='i',b[tot+1]='u',b[tot+2]='m';//如题，这是化学元素，所以要加ium。
	printf("%s\n",b);
}
```

附：其实化学元素不可能到999啦。

117号元素符号为Ts

---

