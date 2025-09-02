# 题目信息

# [CERC2013] Digraphs

## 题目描述

有一些有向字母对，构造一个尽量大（最大$20\times20$）的方阵，使得这个方阵中任意两个相邻字母对（从左到右或从上到下）都不是这些有向字母对中的一个。

## 样例 #1

### 输入

```
2
628
aa
az
ba
bb
bc
bd
be
bf
bg
bh
bi
bj
bk
bl
bm
bn
bo
bp
bq
br
bs
bt
bu
bv
bw
bx
by
ca
cb
cc
cd
ce
cf
cg
ch
ci
cj
ck
cl
cm
cn
co
cp
cq
cr
cs
ct
cu
cv
cw
cx
cy
da
db
dc
dd
de
df
dg
dh
di
dj
dk
dl
dm
dn
do
dp
dq
dr
ds
dt
du
dv
dw
dx
dy
ea
eb
ec
ed
ee
ef
eg
eh
ei
ej
ek
el
em
en
eo
ep
eq
er
es
et
eu
ev
ew
ex
ey
fa
fb
fc
fd
fe
ff
fg
fh
fi
fj
fk
fl
fm
fn
fo
fp
fq
fr
fs
ft
fu
fv
fw
fx
fy
ga
gb
gc
gd
ge
gf
gg
gh
gi
gj
gk
gl
gm
gn
go
gp
gq
gr
gs
gt
gu
gv
gw
gx
gy
ha
hb
hc
hd
he
hf
hg
hh
hi
hj
hk
hl
hm
hn
ho
hp
hq
hr
hs
ht
hu
hv
hw
hx
hy
ia
ib
ic
id
ie
if
ig
ih
ii
ij
ik
il
im
in
io
ip
iq
ir
is
it
iu
iv
iw
ix
iy
ja
jb
jc
jd
je
jf
jg
jh
ji
jj
jk
jl
jm
jn
jo
jp
jq
jr
js
jt
ju
jv
jw
jx
jy
ka
kb
kc
kd
ke
kf
kg
kh
ki
kj
kk
kl
km
kn
ko
kp
kq
kr
ks
kt
ku
kv
kw
kx
ky
la
lb
lc
ld
le
lf
lg
lh
li
lj
lk
ll
lm
ln
lo
lp
lq
lr
ls
lt
lu
lv
lw
lx
ly
ma
mb
mc
md
me
mf
mg
mh
mi
mj
mk
ml
mm
mn
mo
mp
mq
mr
ms
mt
mu
mv
mw
mx
my
na
nb
nc
nd
ne
nf
ng
nh
ni
nj
nk
nl
nm
nn
no
np
nq
nr
ns
nt
nu
nv
nw
nx
ny
oa
ob
oc
od
oe
of
og
oh
oi
oj
ok
ol
om
on
oo
op
oq
or
os
ot
ou
ov
ow
ox
oy
pa
pb
pc
pd
pe
pf
pg
ph
pi
pj
pk
pl
pm
pn
po
pp
pq
pr
ps
pt
pu
pv
pw
px
py
qa
qb
qc
qd
qe
qf
qg
qh
qi
qj
qk
ql
qm
qn
qo
qp
qq
qr
qs
qt
qu
qv
qw
qx
qy
ra
rb
rc
rd
re
rf
rg
rh
ri
rj
rk
rl
rm
rn
ro
rp
rq
rr
rs
rt
ru
rv
rw
rx
ry
sa
sb
sc
sd
se
sf
sg
sh
si
sj
sk
sl
sm
sn
so
sp
sq
sr
ss
st
su
sv
sw
sx
sy
ta
tb
tc
td
te
tf
tg
th
ti
tj
tk
tl
tm
tn
to
tp
tq
tr
ts
tt
tu
tv
tw
tx
ty
ua
ub
uc
ud
ue
uf
ug
uh
ui
uj
uk
ul
um
un
uo
up
uq
ur
us
ut
uu
uv
uw
ux
uy
va
vb
vc
vd
ve
vf
vg
vh
vi
vj
vk
vl
vm
vn
vo
vp
vq
vr
vs
vt
vu
vv
vw
vx
vy
wa
wb
wc
wd
we
wf
wg
wh
wi
wj
wk
wl
wm
wn
wo
wp
wq
wr
ws
wt
wu
wv
ww
wx
wy
xa
xb
xc
xd
xe
xf
xg
xh
xi
xj
xk
xl
xm
xn
xo
xp
xq
xr
xs
xt
xu
xv
xw
xx
xy
ya
yb
yc
yd
ye
yf
yg
yh
yi
yj
yk
yl
ym
yn
yo
yp
yq
yr
ys
yt
yu
yv
yw
yx
yy
za
zb
zc
zd
ze
zf
zg
zh
zi
zj
zk
zl
zm
zn
zo
zp
zq
zr
zs
zt
zu
zv
zw
zx
zy
zz
2
aa
bb
```

### 输出

```
aw
wz
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
abababababababababab
babababababababababa
```

# AI分析结果

### 算法分类
**构造**

### 综合分析与结论
本题的核心在于构造一个尽可能大的方阵，使得方阵中任意两个相邻字母对都不在给定的有向字母对集合中。题解通过图论的方法，将问题转化为在有向图中寻找最长路径或环，并利用动态规划的思想进行转移和求解。最终通过构造路径或环来生成符合条件的方阵。

### 所选题解
#### 题解：035966_L3
**星级：4星**
**关键亮点：**
1. 将问题转化为图论中的最长路径或环问题，思路清晰。
2. 使用动态规划的方法进行状态转移，时间复杂度为 \(O(Tm^4)\)，空间复杂度为 \(O(m^3)\)，在数据范围内可行。
3. 代码实现较为完整，逻辑清晰，易于理解。

**个人心得：**
- 通过将字符矩阵的构造问题转化为图论问题，简化了问题的复杂性。
- 使用动态规划进行状态转移，有效地解决了最长路径或环的查找问题。

**核心代码片段：**
```cpp
bool s[32][32],o[32];
int u[32][32][32];
char r[52];

int go() {
    int n;
    cin>>n;
    memset(s,0,sizeof s);
    memset(u,0,sizeof u);
    memset(r,0,sizeof r);
    memset(o,0,sizeof o);
    for(int i=1;i<=n;i++) {
        char x,y;
        cin>>x>>y;
        x-=96;
        y-=96;
        s[x][y]=true;
    }
    for(int i=1;i<=27;i++)
        s[i][27]=true;
    for(int i=1;i<=27;i++)
        s[27][i]=true;
    for(int i=1;i<=27;i++)
        u[i][i][0]=-1;
    for(int i=1;i<=27;i++)
        for(int j=1;j<=27;j++)
            for(int k=1;k<=27;k++)
                for(int l=1;l<=27;l++) {
                    if(s[j][k]) continue;
                    if(!u[l][j][i-1]) continue;
                    u[l][k][i]=j;
                }
    int c=0,d=0,e=0;
    for(d=1;d<=27;d++) {
        for(int i=1;i<=27;i++)
            if(u[i][i][d]) {
                c=i;
                break;
            }
        if(c) break;
    }
    if(c==0) {
        d=27;
        for(d=27;d>=1;d--) {
            c=0,e=0;
            for(int i=1;i<=27;i++) {
                if(c) break;
                for(int j=1;j<=27;j++)
                if(u[i][j][d]) {
                    c=i;
                    e=j;
                    break;
                }
            }
            if(c) break;
        }
        r[d+1]=e;
        for(int i=d;i>=1;i--) {
            e=u[c][e][i];
            r[i]=e;
        }
        if(d<=1) cout<<'a'<<endl;
        else {
            for(int i=1;i<=d/2+1;i++) {
                for(int j=1;j<=d/2+1;j++)
                    cout<<(char)(r[i+j-1]+96);
                cout<<endl;
            }
        }
    }
    else {
        r[d]=c;
        int p=d;
        for(p=d-1;p>=1;p--) {
            c=u[r[d]][c][p+1];
            r[p]=c;
        }
        for(int i=d+1;i<=39;i++)
            r[i]=r[i-d];
        for(int i=1;i<=20;i++) {
            for(int j=1;j<=20;j++)
                cout<<(char)(r[i+j-1]+96);
            cout<<endl;
        }
    }
    return 0;
}
```

### 扩展思路
- 类似问题可以转化为图论中的路径或环问题，利用动态规划或搜索算法进行求解。
- 在实际应用中，可以通过优化状态转移方程或使用更高效的数据结构来提升算法性能。

### 推荐题目
1. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
2. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：25.73秒