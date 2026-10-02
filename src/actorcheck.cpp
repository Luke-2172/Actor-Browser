#include "browser.cpp"
#include <iostream>
static int fail(int n){std::cerr<<"ActorCheck failed: "<<n<<"\n";return n;}
static void bmp(const wchar_t* path){
 BITMAPFILEHEADER h{};h.bfType=0x4D42;h.bfOffBits=sizeof(h)+40;h.bfSize=h.bfOffBits+rasterWidth()*rasterHeight()*4;
 BITMAPINFOHEADER b{};b.biSize=40;b.biWidth=rasterWidth();b.biHeight=-rasterHeight();b.biPlanes=1;b.biBitCount=32;
 std::ofstream f(path,std::ios::binary);f.write((char*)&h,sizeof(h));f.write((char*)&b,40);f.write((char*)pixels,rasterWidth()*rasterHeight()*4);
}
int wmain(){
 {
  wchar_t temp[MAX_PATH]{},file[MAX_PATH]{};GetTempPathW(MAX_PATH,temp);
  if(!GetTempFileNameW(temp,L"LAB",0,file))return fail(40);
  if(!CopyFileW(L"package/NVSE/Plugins/LukesActorBrowser/Fonts/ShareTechMono-Regular.ttf",file,FALSE))return fail(41);
  VectorFont memoryFont;memoryFont.load(file,L"Share Tech Mono",FW_NORMAL);
  if(!DeleteFileW(file))return fail(42);
  std::vector<uint32_t> out(400*80,0);
  memoryFont.draw(out.data(),400,80,0,0,400,80,"Memory font",37,RGB(255,255,255));
  if(std::none_of(out.begin(),out.end(),[](uint32_t p){return p!=0;}))return fail(43);
  VectorFont missing;loadMenuFont(missing,file,L"Share Tech Mono",FW_NORMAL,L"Consolas");
  std::fill(out.begin(),out.end(),0);
  missing.draw(out.data(),400,80,0,0,400,80,"Fallback",37,RGB(255,255,255));
  if(std::none_of(out.begin(),out.end(),[](uint32_t p){return p!=0;}))return fail(44);
  std::cout<<"PASS: memory font renders after file deletion; missing font uses fallback"<<std::endl;
 }
 loadMenuFonts(L"package/NVSE/Plugins/LukesActorBrowser/Fonts/");
 {
  for(const auto* name:{"VALUES","SPAWN","SETTINGS","READ / CAPTURE TARGET","+","-"}){
   std::vector<uint32_t> out(600*90,0);vanillaGlow.draw(out.data(),600,90,0,0,600,90,name,44,RGB(255,255,255),true);
   int l=600,r=-1,t=90,b=-1;
   for(int y=0;y<90;++y)for(int x=0;x<600;++x)if((out[y*600+x]&255)>=96){l=std::min(l,x);r=std::max(r,x);t=std::min(t,y);b=std::max(b,y);}
   if(r<l||std::abs(l+r-599)>4||std::abs(t+b-89)>4){std::cerr<<"Misaligned control: "<<name<<std::endl;return 23;}
  }
  std::cout<<"PASS: visible button glyph bounds centred horizontally and vertically"<<std::endl;
  renderScale=3;
 }
 if(hotkey!=VK_F10||ActorValueCount!=30)return fail(1);
 {vf::Font f;f.height=16;f.width=f.rows=1;f.rgba={255,255,255,255};f.glyphs['A']={0,0,0,1,0,0,1,1,1,8,12,0,0,12};
  std::vector<uint32_t> out(100,0x112233);f.draw(out.data(),10,10,2,2,4,4,"AAA",16,RGB(255,200,100));bool changed=false;
  for(int y=0;y<10;++y)for(int x=0;x<10;++x){if(x>=2&&x<6&&y>=2&&y<6){changed|=out[y*10+x]!=0x112233;}else if(out[y*10+x]!=0x112233)return fail(21);}
  // Use a box that intersects the glyph body, without truncation.
  f.draw(out.data(),10,10,2,-4,8,14,"A",16,RGB(255,200,100));
  for(auto p:out)changed|=p!=0x112233;if(!changed)return fail(22);
 }
 if(!ib::itemType("NPC_")||!ib::itemType("CREA")||ib::itemType("WEAP")||ib::itemType("LVLC"))return fail(2);
 double n;for(auto s:{"nan","inf","1e999","1;quit","","1x"})if(actorValueNumber(s,n))return fail(3);
 if(!actorValueNumber("125.5",n)||n!=125.5)return fail(4);
 wchar_t tmp[MAX_PATH];GetTempPathW(MAX_PATH,tmp);bridgePath=std::wstring(tmp)+L"LukesActorBrowser-test-"+std::to_wstring(GetCurrentProcessId())+L".ini";
 sessionToken=456;WritePrivateProfileStringW(L"Bridge",L"Ready",L"456",bridgePath.c_str());
 plugins={L"FalloutNV.esm"};pluginIndex=0;catalog.items={ib::Item{0x123,"NPC_","Test NCR Trooper","TestTrooper",false},ib::Item{0x456,"CREA","Test Deathclaw","TestDeathclaw",false}};
  catalog.items.push_back({0x789,"NPC_","Template","GenericNPC",false});
 catalog.items.push_back({0x790,"CREA","Deathclaw","CrDeathclawTEMPLATE",true});
 for(bool overrides:{false,true})for(int cat:{0,1,2}){
  showOverrides=overrides;category=cat;filterItems();
  for(auto index:visible)if(catalog.items[index].id==0x789||catalog.items[index].id==0x790)return fail(24);
  if(visible.size()!=(cat==0?2u:1u))return fail(25);
 }
 query="template";filterItems();if(!visible.empty())return fail(26);
  query.clear();category=0;showOverrides=true;showTemplates=true;filterItems();
 if(visible.size()!=4)return fail(27);
 query="template";filterItems();if(visible.size()!=2)return fail(28);
  iniPath=bridgePath+L".settings.ini";
 WritePrivateProfileStringW(L"Browser",L"ShowTemplates",L"1.000000",iniPath.c_str());config();
 if(!showTemplates)return fail(29);
 settingsPage=true;cursorX=550;cursorY=395;click();
 if(showTemplates||GetPrivateProfileIntW(L"Browser",L"ShowTemplates",1,iniPath.c_str())!=0)return fail(30);
 settingsPage=false;DeleteFileW(iniPath.c_str());
 query.clear();showTemplates=false;category=0;showOverrides=false;
 std::cout<<"PASS: template display names and editor IDs hidden across categories, search and overrides"<<std::endl;
 filterPlugins();filterItems();quantity=100;requestItem();
 if(bridgeNumber(L"Request",L"Action")!=0||bridgeNumber(L"Request",L"Count")!=5||!bridgeNumber(L"Request",L"Pending"))return fail(5);
 WritePrivateProfileStringW(L"Request",L"Pending",L"0",bridgePath.c_str());
 snapshotReady=false;requestValue(2);if(bridgeNumber(L"Request",L"Pending"))return fail(6);
 snapshotReady=true;valueInput="100001";requestValue(2);if(bridgeNumber(L"Request",L"Pending"))return fail(7);
 valueInput="125.5";requestValue(2);if(bridgeNumber(L"Request",L"Action")!=2||bridgeNumber(L"Request",L"AV")!=0||snapshotReady)return fail(8);
 WritePrivateProfileStringW(L"Request",L"Pending",L"0",bridgePath.c_str());
 category=2;filterItems();if(visible.size()!=1||catalog.items[visible[0]].type!="CREA")return fail(9);
 category=0;filterItems();status="Layout preview using fixture actors; not an in-game screenshot.";
 if(!createCanvas())return fail(10);drawCanvas();bmp(L"build/Spawn-preview.bmp");
 valuesPage=true;targetName="Player [00000014]";baseValue="100";currentValue="125";drawCanvas();bmp(L"build/Values-preview.bmp");
 cursorX=400;cursorY=400;scrollWheel(-240);if(avScroll!=6)return fail(11);
 settingsPage=true;valuesPage=false;drawCanvas();bmp(L"build/Settings-preview.bmp");
 destroyCanvas();DeleteFileW(bridgePath.c_str());
 std::cout<<"PASS: actor categories, F10 default, finite number validation, spawn limit, stale snapshot/apply range checks, value scrolling and three page renders\n";return 0;
}




