/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.fennex.emptyproject;

import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

import com.fennex.modules.ActivityResultNotifier;
import com.diwublog.AnalyticX.AnalyticXBridge;
import com.flurry.android.FlurryAgent;
import com.fennex.emptyproject.R;

public class EmptyProject extends ActivityResultNotifier {

	private static volatile EmptyProject instance = null;
	//Return your Google Store private key for billing if you use in-app purchase
	public String getPublicKey()
	{
		return "";
	}
	
    //Return your small icon for notification
	public int getSmallIcon()
	{
	    return 0;
		//return R.drawable.icon;
	}
	
	//Useful for Video Player only
	public Uri getUriFromFileName(String fileName)
	{
		return null;
	}
	
	public static EmptyProject getInstance()
	{
		return instance;
	}
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		AnalyticXBridge.sessionContext = this.getApplicationContext();
    	instance = this;
	}

    //Tell InAppWrapper if a particular productID is a consumable
	@Override
	public boolean isConsumable(String productID) {
		// TODO Auto-generated method stub
		return false;
	}
}
