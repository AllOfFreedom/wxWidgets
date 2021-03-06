///////////////////////////////////////////////////////////////////////////////
// Name:        tests/toplevel/toplevel.cpp
// Purpose:     Tests for wxTopLevelWindow
// Author:      Kevin Ollivier
// Created:     2008-05-25
// Copyright:   (c) 2009 Kevin Ollivier <kevino@theolliviers.com>
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/dialog.h"
    #include "wx/frame.h"
    #include "wx/textctrl.h"
    #include "wx/toplevel.h"
#endif // WX_PRECOMP

#include "wx/evtloop.h"

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class TopLevelWindowTestCase : public CppUnit::TestCase
{
public:
    TopLevelWindowTestCase() { }

private:
    CPPUNIT_TEST_SUITE( TopLevelWindowTestCase );
        CPPUNIT_TEST( DialogShowTest );
        CPPUNIT_TEST( FrameShowTest );
    CPPUNIT_TEST_SUITE_END();

    void DialogShowTest();
    void FrameShowTest();
    void TopLevelWindowShowTest(wxTopLevelWindow* tlw);

    wxDECLARE_NO_COPY_CLASS(TopLevelWindowTestCase);
};

// register in the unnamed registry so that these tests are run by default
//CPPUNIT_TEST_SUITE_REGISTRATION( TopLevelWindowTestCase );

// also include in its own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( TopLevelWindowTestCase, "fixme" );

// ----------------------------------------------------------------------------
// tests themselves
// ----------------------------------------------------------------------------

void TopLevelWindowTestCase::DialogShowTest()
{
    wxDialog* dialog = new wxDialog(NULL, -1, "Dialog Test");
    TopLevelWindowShowTest(dialog);
    dialog->Destroy();
}

void TopLevelWindowTestCase::FrameShowTest()
{
    wxFrame* frame = new wxFrame(NULL, -1, "Frame test");
    TopLevelWindowShowTest(frame);
    frame->Destroy();
}

void TopLevelWindowTestCase::TopLevelWindowShowTest(wxTopLevelWindow* tlw)
{
    CHECK(!tlw->IsShown());

    wxTextCtrl* textCtrl = new wxTextCtrl(tlw, -1, "test");
    textCtrl->SetFocus();

// only run this test on platforms where ShowWithoutActivating is implemented.
#if defined(__WXMSW__) || defined(__WXMAC__)
    tlw->ShowWithoutActivating();
    CHECK(tlw->IsShown());
    CHECK(!tlw->IsActive());

    tlw->Hide();
    CHECK(!tlw->IsShown());
    CHECK(!tlw->IsActive());
#endif

    tlw->Show(true);

    // wxGTK needs many event loop iterations before the TLW becomes active and
    // this doesn't happen in this test, so avoid checking for it.
#ifndef __WXGTK__
    CHECK(tlw->IsActive());
#endif
    CHECK(tlw->IsShown());

    tlw->Hide();
    CHECK(!tlw->IsShown());
#ifndef __WXGTK__
    CHECK(tlw->IsActive());
#endif
}
