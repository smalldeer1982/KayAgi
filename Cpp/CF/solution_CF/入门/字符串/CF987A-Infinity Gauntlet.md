# Infinity Gauntlet

## 题目描述

# 题目大意
你偷看了Thanos的无尽手套，手套上有6颗无限宝石：
- the **Power** Gem of **purple** color, 紫色的力量宝石
- the **Time** Gem of **green** color, 绿色的时间宝石
- the **Space** Gem of **blue** color, 蓝色的空间宝石
- the **Soul** Gem of **orange** color, 橙色的灵魂宝石
- the **Reality** Gem of **red** color, 红色的现实宝石
- the **Mind** Gem of **yellow** color. 黄色的心灵宝石

现在给出你偷看到的宝石的**颜色**，请你确定缺少了哪些宝石（**名称**）

## 样例 #1

### 输入

```
4
red
purple
yellow
orange
```

### 输出

```
2
Space
Time
```

## 样例 #2

### 输入

```
0
```

### 输出

```
6
Time
Space
Power
Reality
Mind
Soul
```

# 题解

## 作者：文·和 (赞：7)

## 首要任务：讲题   ；次要任务：普及漫威基础知识

思路：不用多说了，把六颗无限宝石的名字存下来，一个一个比对，而且不用考虑顺序，最后输出。

贴出代码（其余细节在代码中解释）

```
#include <bits/stdc++.h>
using namespace std;
string s[6]={{"Power"},{"Space"},{"Time"},{"Soul"},{"Reality"},{"Mind"}},j;   //存下来每颗无限宝石和输入串
int n,i,k,l,ok[6];      //看到个数为n，ok表示是否看见此宝石
int main(){
cin>>n;
for(i=1;i<=n;i++){
cin>>j;                  //一边读一边处理
if(j=="purple") ok[0]=1;
if(j=="blue") ok[1]=1;
if(j=="green") ok[2]=1;
if(j=="orange") ok[3]=1;
if(j=="red") ok[4]=1;
if(j=="yellow") ok[5]=1;    //看到宝石即标记拥有
}
cout<<6-n<<endl;   //此时将n转化为没有出现的宝石数
for(i=0;i<=5;i++){
if(ok[i]==0) cout<<s[i]<<endl;   //如果没出现则输出
}
return 0;
}
```

## 以下为漫威知识普及（每颗宝石的介绍，影版）

------------

Power（力量宝石）：紫色，容器为“宇宙灵球”。星爵于魔拉格发现，《银河护卫队1》结尾被星爵留在山达尔星。《银河护卫队1》中被星爵用来击杀罗南。第二次出现于《复仇者联盟3》片头，此时力量宝石已经被灭霸（Thanos）获得，灭霸用它摧毁阿斯加德飞船，在泰坦星时用它攻击奇异博士。

Space（空间宝石）：蓝色，容器为“宇宙魔方”。几乎贯穿整个漫威时间线。《雷神1》开始时说明宇宙魔方被留在挪威滕斯贝格。二战时被红骷髅发现并带回研究。
《美国队长1》结尾将红骷髅传送到沃弥尔成为灵魂宝石领路人并掉入大洋。后来被钢铁侠之父打捞出来研究（“天马计划”），发现魔方能量元素却无法合成。于是将原子结构图放入博览会场馆设计图并留给了钢铁侠。钢铁侠合成了这个元素并作为战甲东西，代替了有毒的钯元素。此前，惊奇队长受命打爆宇宙魔方的光速引擎，获得宝石的力量被带回克里星洗脑，觉醒之后夺回。《复仇者联盟1》结尾被带回阿斯加德。《复仇者联盟3》被灭霸从阿斯加德飞船上获得。灭霸用来挡洛基的匕首和在泰坦星上吸收火焰再喷出以及跑路。

Time（时间宝石）：绿色，容器为“阿戈摩托之眼”。一直被至上尊者保护。《复仇者联盟3》被奇异博士当筹码交给灭霸换下钢铁侠。灭霸用来复活幻视和治疗伤口(很小的细节)。

Soul（灵魂宝石）：橙色，无容器，一直存放在沃弥尔。《复仇者联盟3》被灭霸用卡魔拉换得。灭霸在泰坦星抓住奇异博士中起到了小作用。（其余暂时不知）

Reality（现实宝石）：红色，容器为“以太粒子”，为暗黑精灵的武器，《雷神2》中被简（雷神女友）吸收又被玛勒基斯取出，《雷神2》结尾被阿斯加德战士交给收藏家。《复仇者联盟3》被灭霸取得。灭霸用于制造幻象带走卡魔拉以及抓住奇异博士。

Mind（心灵宝石）：黄色，容器为权杖，《复仇者联盟1》被灭霸交给洛基去抢空间宝石。洛基失败后权杖被九头蛇偷走并研究，改造了女巫和快银。《复仇者联盟2》被复仇者联盟夺回交给钢铁侠研究，钢铁侠不小心制造了人工智能反派奥创抢走权杖，取出宝石作为新躯体的能量源。所幸新躯体被复仇者抢回并传入贾维斯的意识，成为“幻视”。《复仇者联盟3》被偷袭导致失去战斗力。结尾为阻止灭霸打响指被女巫摧毁但被灭霸用时间宝石复活并取下宝石。洛基用它控制了鹰眼和席尔维格，幻视用来发射激光。

灭霸宝石获得顺序：力量->空间->现实->灵魂->时间->心灵->响指->摧毁宝石

# 打字这么累，给个通过呗！

---

## 作者：OdtreePrince (赞：0)

# -字符串-

用不来map的我只能俯首去打表，哎~~~

表不难打，输出的值必为6-n,理由不必说了吧

其次，只要没被标记过的，统统输出！

测评有些慢，希望改进！

~~~
#include<bits/stdc++.h>
using namespace std;
string s[10],name[6]={"Power","Time","Space","Soul","Reality","Mind"};
int n,b[6];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        cin>>s[i];
        if(s[i]=="purple"){
            b[0]=1;
        }
        if(s[i]=="green"){
            b[1]=1;
        }
        if(s[i]=="blue"){
            b[2]=1;
        }
        if(s[i]=="orange"){
            b[3]=1;
        }
        if(s[i]=="red"){
            b[4]=1;
        }
        if(s[i]=="yellow"){
            b[5]=1;
        }
    }
    cout<<6-n<<endl;
    for(int i=0;i<6;i++){
        if(!b[i]){
            cout<<name[i]<<endl;
        }
    }
    return 0;
}
~~~

---

## 作者：_Qer (赞：0)

这里提供一种map的做法

用string存好每个宝石的名字，再用一个map存颜色对应宝石的下标。

输入时直接用map取对应宝石的编号，将宝石名字改成某个标记，输出时判断

也可以开数组存已有宝石的下标，输出时判断是否出现即可

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string gems[10] = {"Power", "Time", "Space", "Soul", "Reality", "Mind"}, color;
//宝石名字，输入的颜色
map<string, int> colortogem;//map把string转成int
int main() {
    colortogem["purple"] = 0;
    colortogem["green"] = 1;
    colortogem["blue"] = 2;
    colortogem["orange"] = 3;
    colortogem["red"] = 4;
    colortogem["yellow"] = 5;
    //以上初始化颜色对应宝石下标
    cin >> n;
    cout << 6 - n << endl;//总共6个宝石，有n个宝石，6-n即为缺少宝石数量
    for (int i = 1; i <= n; ++i) {
        cin >> color;
        gems[colortogem[color]] = "has";//对应宝石名称修改一下
    }
    for (int i = 0; i < 6; ++i) {
        if (gems[i] != "has") {//未拥有宝石
            cout << gems[i] << endl;
        }
    }
    return 0;
}

```

---

## 作者：Victory_Defeat (赞：0)

# 这题其实非常的简单，思路如下：首先读入，然后将所有已有的宝石标记一下，统计未有宝石并输出。（注：已有所有宝石需输出0）

# 详见代码注释：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m;
bool need[10];//是否需要宝石
string s,all[10]={"","Power","Space","Reality","Soul","Time","Mind"};//将所有宝石存储下来，此处按灭霸获取宝石的顺序
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if(s=="purple")need[1]=1;//6种宝石及其颜色的判断
        if(s=="blue")need[2]=1;
        if(s=="red")need[3]=1;
        if(s=="orange")need[4]=1;
        if(s=="green")need[5]=1;
        if(s=="yellow")need[6]=1;
    }
    for(int i=1;i<=6;i++)
        if(!need[i])m++;//统计所需宝石数
    printf("%d\n",m);
    for(int i=1;i<=6;i++)if(!need[i])cout<<all[i]<<endl;//输出需要的宝石
}
/*
借此在这里声明一下：存储顺序及输出顺序是随意的，可以按自己想法输出，无须按我的方法存储
最后声明一下：
抄袭可耻！
抄袭可耻！
抄袭可耻！
*/
```

---

