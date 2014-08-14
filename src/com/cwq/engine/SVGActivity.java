package com.cwq.engine;

import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;

import com.cwq.object.svg.SVG;
import com.cwq.object.svg.SVGHandler;
import com.cwq.scene.Scene;

import android.app.Activity;
import android.os.Bundle;

public class SVGActivity extends Activity {
	
	public static final String TAG = "SVGActivity";
	private Scene myScene;
	private SVG svg;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		myScene = new Scene(this);
		setContentView(myScene);
		
		try {
			SAXParserFactory factory = SAXParserFactory.newInstance();
			SAXParser parser = factory.newSAXParser();
			XMLReader reader = parser.getXMLReader();
			SVGHandler handler = new SVGHandler();
			reader.setContentHandler(handler);
			InputSource input = new InputSource(this.getAssets().open("rect.svg"));
			reader.parse(input);
			svg = handler.getSVG();
			myScene.addObj(svg);
		} catch (ParserConfigurationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SAXException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
	}
	
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		myScene.onPause();
	}
	
	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		myScene.onResume();
	}

}
