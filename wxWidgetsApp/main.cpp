#include <wx/wx.h>
#include <vector>
#include <wx/button.h>
#include <wx/event.h>
#include <wx/colordlg.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void OnTextEntered(wxCommandEvent& event);
    void Form_Paint(wxPaintEvent& e);
    void Save_File_Button(wxCommandEvent& e);
    void OnCheckBox(wxCommandEvent& e);
    void OnChoice(wxCommandEvent& e);
    void OnColorPicker(wxCommandEvent& event);
    void OnScroll(wxCommandEvent& e);
    wxPanel* draw_panel;
    wxPanel* button_panel;
    wxCheckBox* checkbox;
    wxBitmap banana_bitmap; 
    wxBitmap MyBitmap;
    wxImage MyImage;
    wxTextCtrl* text_ctrl;
    wxString enteredText= "";
    wxChoice* choice_ctrl;
    wxScrollBar* scrollbar;
    wxGauge* gauge;
    int selectedChoice = 0;
    int scrollPos = 0;
    wxColor starcolor = *wxWHITE;
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("hello world", wxDefaultPosition, wxDefaultSize);
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    SetTitle(_("czesc"));
    SetIcon(wxNullIcon);
    SetSize(8, 8, 294, 321);
    Center();

    draw_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 500));
    button_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 500));
    button_panel->SetBackgroundColour(wxColor(0, 0, 122));
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(draw_panel, 2, wxEXPAND);
    sizer->Add(button_panel, 1, wxEXPAND);

    SetSizerAndFit(sizer);

    text_ctrl = new wxTextCtrl(button_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    text_ctrl->Bind(wxEVT_TEXT_ENTER, &MyFrame::OnTextEntered, this);
    
    wxButton* save_button = new wxButton(button_panel, wxID_ANY, "save to file");
    save_button->Bind(wxEVT_BUTTON, &MyFrame::Save_File_Button, this);

    checkbox = new wxCheckBox(button_panel, wxID_ANY, "Checkbox", wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
    checkbox->Bind(wxEVT_CHECKBOX, &MyFrame::OnCheckBox, this);

    wxString choices[] = { "gwiazda", "ksiezyc", "slonce" };
    choice_ctrl = new wxChoice(button_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, WXSIZEOF(choices), choices);
    choice_ctrl->Bind(wxEVT_CHOICE, &MyFrame::OnChoice, this);

    scrollbar = new wxScrollBar(button_panel, wxID_ANY);
    scrollbar->SetScrollbar(0, 10, 100, 5);
    scrollbar->Bind(wxEVT_SCROLL_THUMBRELEASE, &MyFrame::OnScroll, this);

    wxButton* color_picker_button = new wxButton(button_panel, wxID_ANY, "kolor gwiazdki"); 
    color_picker_button->Bind(wxEVT_BUTTON, &MyFrame::OnColorPicker, this); 

    gauge = new wxGauge(button_panel, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
    buttonSizer->Add(save_button, wxSizerFlags(1).Expand().Border(wxALL, 10));
    buttonSizer->Add(checkbox, wxSizerFlags(1).Expand().Border(wxALL, 10));
    buttonSizer->Add(text_ctrl, wxSizerFlags(1).Expand().Border(wxALL, 10));
    buttonSizer->Add(choice_ctrl, wxSizerFlags(1).Expand().Border(wxALL, 10));
    buttonSizer->Add(scrollbar, wxSizerFlags(1).Expand().Border(wxALL, 10));
    buttonSizer->Add(color_picker_button, wxSizerFlags(1).Expand().Border(wxALL, 10));
    buttonSizer->Add(gauge, wxSizerFlags(1).Expand().Border(wxALL, 10));
    button_panel->SetSizer(buttonSizer);



    draw_panel->Bind(wxEVT_PAINT, &MyFrame::Form_Paint, this);
    MyImage.AddHandler(new wxPNGHandler);
    // Załaduj obrazek banan.png
    //banana_bitmap = new wxBitmap("C:/Users/matro/source/repos/Lab33/Lab33/banan.png", wxBITMAP_TYPE_PNG); // Sprawdź, czy ścieżka do obrazka jest poprawna
}

void MyFrame::Save_File_Button(wxCommandEvent& event) {
    wxInitAllImageHandlers();
    draw_panel->Refresh();

    wxMilliSleep(100);

    wxBitmap bitmap(draw_panel->GetSize());

    wxMemoryDC memDC;
    memDC.SelectObject(bitmap);

    
    wxClientDC dc(draw_panel);

    memDC.Blit(0, 0, draw_panel->GetSize().GetWidth(), draw_panel->GetSize().GetHeight(),
        &dc, 0, 0);

    wxString defaultDir = wxGetCwd();
    wxString defaultFile = "obrazek.png";
    wxString wildcard = "PNG files (*.png)|*.png";

    wxFileDialog saveFileDialog(this, _("Save file"), defaultDir, defaultFile, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return; 
    }

    // Pobranie ścieżki do wybranego pliku
    wxString filePath = saveFileDialog.GetPath();


    bitmap.SaveFile(filePath, wxBITMAP_TYPE_PNG);
   
}

void MyFrame::Form_Paint(wxPaintEvent& event) {
    wxPaintDC dc(draw_panel);
    //dc.SelectObject(MyBitmap);
    dc.SetBackground(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_SOLID));
    dc.Clear();
    dc.DrawLine(400, 300, 400, 200);//cialo
    dc.DrawLine(400, 200, 450, 250);
    dc.DrawLine(400, 200, 350-scrollPos, 250-scrollPos);
    dc.DrawLine(400, 300, 450, 450);
    dc.DrawLine(400, 300, 350, 450);
    dc.DrawCircle(400, 150, 50); // glowa

    wxFont font(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);
    dc.DrawText("tekst", 100, 400);

    if (selectedChoice == 0) {
        
        wxPoint center(100, 100);
        int radius = 30; 

       
        wxPoint points[10];
        for (int i = 0; i < 5; ++i) {
            double angle = 2 * M_PI / 5 * i - M_PI / 2;
            points[2 * i] = wxPoint(center.x + radius * cos(angle), center.y + radius * sin(angle));
            angle += 2 * M_PI / 5 / 2;
            points[2 * i + 1] = wxPoint(center.x + radius * 0.5 * cos(angle), center.y + radius * 0.5 * sin(angle));
        }


        dc.SetBrush(starcolor);
        dc.DrawPolygon(10, points);
    }
    else if (selectedChoice == 1) {
        wxPoint p1(100, 100);
        wxPoint p2(150, 150);
        wxPoint k1(120, 120);
        wxPoint k2(140, 100);
        dc.DrawArc(p1, p2, k1);
        dc.DrawArc(p1, p2, k2);
    }
    else {
        dc.SetBrush(*wxYELLOW_BRUSH);
        dc.DrawCircle(100, 100, 40);
    }

    

    

 
    
    dc.SetBrush(*wxTRANSPARENT_BRUSH);

    dc.DrawEllipse(410, 110, 20, 40); // Lewe oko
    dc.DrawEllipse(370, 110, 20, 40); // Prawe oko
    if (enteredText.length() > 1) {
        wxFont font2(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        dc.SetFont(font2);
        dc.DrawRotatedText(enteredText, 250, 500, 90);
    }
    else {
        wxFont font2(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        dc.SetFont(font2);
        dc.DrawRotatedText("tekst", 250, 500, 90);
    }
    

    if (banana_bitmap.Ok()) {
        dc.DrawBitmap(banana_bitmap, 250-scrollPos, 250-scrollPos);
        dc.DrawEllipticArc(385, 160, 30, 30, 180, 0);
    }
    else {
        dc.DrawEllipticArc(385, 170, 30, 30, 0, 180);
    }

}

void MyFrame::OnCheckBox(wxCommandEvent& event) {
    // Jeśli checkbox jest zaznaczony, wklej obrazek banan.png
    if (checkbox->IsChecked()) {
        if (MyImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG)) {

            MyImage.Rescale(120, 80);
        }
        wxImage TempImg(MyImage);
        TempImg.Rescale(120, 80);
        MyImage.Paste(TempImg, MyImage.GetWidth() - 120, 0);
        banana_bitmap = wxBitmap(MyImage);
        if (banana_bitmap.Ok()) {
            Refresh();
        }
        //Refresh();
    }
    else {
        banana_bitmap = wxNullBitmap;
        Refresh();
    }
}

void MyFrame::OnTextEntered(wxCommandEvent& event) {
    enteredText = text_ctrl->GetValue();
    Refresh();
}

void MyFrame::OnChoice(wxCommandEvent& event) {
    selectedChoice = choice_ctrl->GetSelection(); 
   
    Refresh();
}

void MyFrame::OnScroll(wxCommandEvent& event) {
    scrollPos = scrollbar->GetThumbPosition();
    gauge->SetValue(scrollPos);
    Refresh();
}

void MyFrame::OnColorPicker(wxCommandEvent& event) {
    wxColourData data;
    wxColour color;

    data.SetColour(color);

    wxColourDialog dialog(this, &data);

  
    if (dialog.ShowModal() == wxID_OK) {
       
        wxColourData retData = dialog.GetColourData();
        color = retData.GetColour();
        starcolor = color;
        
    }
    Refresh();
}