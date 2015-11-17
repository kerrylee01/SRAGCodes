
TGraph* DrawTest(std::string sSpectralFile, bool bDraw = false)
{
  std::ifstream ifIn(sSpectralFile.c_str());
  TCanvas *c = new TCanvas("c1","c1");
  c->SetLogx();
  c->SetLogy();
  TGraph *g = new TGraph();
  int iCount = 0;
  double dX, dY;
  while (!(ifIn.eof())) {
    ifIn >> dX >> dY;
    if( !(ifIn.good()) ) break;
    g->SetPoint(iCount, dX, dY);
    iCount++;
  }
  if(bDraw) g->Draw("apl");
  return g;
}

void MakeSplineFunction(std::string sSpectralFile)
{
  std::ifstream ifIn(sSpectralFile.c_str());
  //TCanvas *c = new TCanvas("c1","c1");
  //c->SetLogx();
  //c->SetLogy();
  TGraph *g = new TGraph();
  int iCount = 0;
  double dX, dY;
  while (!(ifIn.eof())) {
    ifIn >> dX >> dY;
    if( !(ifIn.good()) ) break;
    g->SetPoint(iCount, log10(dX), log10(dY));
    iCount++;
  }
  //g->Draw("apl");
  TSpline3 *spline = new TSpline3("test", g);
  spline->SaveAs("test.cpp");
}

TH1F* Make1DHisto(std::string sSpectralFile)
{ 
  //
  //create a 1D histogram with the variable bin widths in filename
  //This can be used in plotting the energy spectrum from the tree in MakeTree()
  //
  std::ifstream ifIn(sSpectralFile.c_str());
  std::vector<double> v_dX;
  double dX, dY;
  while (!(ifIn.eof())) {
    ifIn >> dX >> dY;
    if( !(ifIn.good()) ) break;
    v_dX.push_back(dX);
  }
  const int iSize = v_dX.size();
  double a_dX[iSize];
  for(int i = 0; i < iSize; i++) a_dX[i] = v_dX[i];
  return new TH1F("h","h", iSize - 1, a_dX);
}

TTree* MakeTree(std::string filename)
{
  TTree *tree = new TTree("tree","tree");
  tree->ReadFile(filename.c_str(),"pid/I:energy/D:x:y:z:tx:ty:tz:weight");
  //tree->StartViewer();
  return tree;
}

void Analysis(std::string sSpectralFile, std::string sOutFile, bool bDraw = false)
{
  TGraph *g = DrawTest(sSpectralFile, false);
  TH1F *h = Make1DHisto(sSpectralFile);
  TTree *tree = MakeTree(sOutFile);
  tree->Draw("energy>>h","pid==1","goff");
  h->Scale(g->Integral()/h->Integral());
  h->Draw();
  g->Draw("lp");
}
