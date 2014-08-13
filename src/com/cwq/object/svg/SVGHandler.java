package com.cwq.object.svg;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import android.graphics.PointF;

import com.cwq.object.Line;
import com.cwq.object.Rectangle;

public class SVGHandler extends DefaultHandler {
	
	private static final String TAG_SVG = "svg";
	
	private static final String UNIT_PX = "px";
	
	private static final String TAG_CIRCLE = "circle";
	private static final String TAG_ELLIPSE = "ellipse";
	private static final String TAG_LINE = "line";
	private static final String TAG_PATH = "path";
	private static final String TAG_POLYGON = "polygon";
	private static final String TAG_POLYLINE = "polyline";
	private static final String TAG_RECTANGLE = "rect";
	
	private static final String ATTRIBUTE_X = "x";
	private static final String ATTRIBUTE_Y = "y";
	private static final String ATTRIBUTE_X1 = "x1";
	private static final String ATTRIBUTE_Y1 = "y1";
	private static final String ATTRIBUTE_X2 = "x2";
	private static final String ATTRIBUTE_Y2 = "y2";
	private static final String ATTRIBUTE_WIDTH = "width";
	private static final String ATTRIBUTE_HEIGHT = "height";
	private static final String ATTRIBUTE_FILL = "fill";
	private static final String ATTRIBUTE_NONE = "none";
	private static final String ATTRIBUTE_FILL_OPACITY = "fill-opacity";
	
	private static final String COLOR_RED = "red";
	private static final String COLOR_BLUE = "blue";
	private static final String COLOR_GREEN = "green";
	
	private SVG svg;
	
	public SVG getSVG() {
		return svg;
	}

	@Override
	public void startDocument() throws SAXException {
		// TODO Auto-generated method stub
		svg = new SVG();
	}
	
	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attributes) throws SAXException {
		// TODO Auto-generated method stub
		if (localName.equals(TAG_SVG)) {
			this.parseSVG(attributes);
		} else if (localName.equals(TAG_LINE)) {
			this.parseLine(attributes);
		} else if (localName.equals(TAG_RECTANGLE)) {
			this.parseRect(attributes);
		}
	}
	
	private void parseSVG(final Attributes pAttributes) {
		svg.setWidth(this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_WIDTH)));
		svg.setHeight(this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_HEIGHT)));
	}
	
	private void parseLine(final Attributes pAttributes) {
		float x1 = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_X1));
		float y1 = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_Y1));
		float x2 = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_X2));
		float y2 = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_Y2));
		float normalizedX1, normalizedY1, normalizedX2, normalizedY2;
		if (svg.getHeight() > svg.getWidth()) {
			normalizedX1 = (x1 / svg.getWidth()) * 2 - 1;
			normalizedY1 = -((y1 / svg.getHeight()) * 2 - 1) * svg.getHeight() / svg.getWidth();
			normalizedX2 = (x2 / svg.getWidth()) * 2 - 1;
			normalizedY2 = -((y2 / svg.getHeight()) * 2 - 1) * svg.getHeight() / svg.getWidth();
		} else {
			normalizedX1 = ((x1 / svg.getWidth()) * 2 - 1) * svg.getWidth() / svg.getHeight();
			normalizedY1 = -((y1 / svg.getHeight()) * 2 - 1);
			normalizedX2 = ((x2 / svg.getWidth()) * 2 - 1) * svg.getWidth() / svg.getHeight();
			normalizedY2 = -((y2 / svg.getHeight()) * 2 - 1);
		}
		svg.addObject(new Line(new PointF(normalizedX1, normalizedY1),
				new PointF(normalizedX2, normalizedY2)));
	}
	
	private void parseRect(final Attributes pAttributes) {
		float x = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_X));
		float y = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_Y));
		float width = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_WIDTH)) / svg.getWidth();
		float height = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_HEIGHT)) / svg.getHeight();
		String fill = this.getStringAttribute(pAttributes, ATTRIBUTE_FILL);
		boolean isEmpty = ATTRIBUTE_NONE.equals(fill);
		float normalizedX, normalizedY;
		if (svg.getHeight() > svg.getWidth()) {
			normalizedX = (x / svg.getWidth()) * 2 - 1;
			normalizedY = -((y / svg.getHeight()) * 2 - 1) * svg.getHeight() / svg.getWidth();
		} else {
			normalizedX = ((x / svg.getWidth()) * 2 - 1) * svg.getWidth() / svg.getHeight();
			normalizedY = -((y / svg.getHeight()) * 2 - 1);
		}
		Rectangle rectangle = new Rectangle(normalizedX, normalizedY, width, height, isEmpty);
		if (!isEmpty) {
			float[] color = {0, 0, 0, 1};
			if (COLOR_RED.equals(fill)) {
				color[0] = 1;
			} else if (COLOR_GREEN.equals(fill)) {
				color[1] = 1;
			} else if (COLOR_BLUE.equals(fill)) {
				color[2] = 1;
			}
			Float opacity = this.extractFloatAttribute(this.getStringAttribute(pAttributes, ATTRIBUTE_FILL_OPACITY));
			if (opacity != null) {
				color[3] = opacity;
			}
			rectangle.setColor(color[0], color[1], color[2], color[3]);
		}
		svg.addObject(rectangle);
	}
	
	private String getStringAttribute(final Attributes pAttributes, final String pAttributeName) {
		final int attributeCount = pAttributes.getLength();
		for (int i = 0; i < attributeCount; i++) {
			if (pAttributes.getLocalName(i).equals(pAttributeName)) {
				return pAttributes.getValue(i);
			}
		}
		return null;
	}
	
	private Float extractFloatAttribute(final String pString) {
		if (pString == null) {
			return null;
		} else {
			try {
				if (pString.endsWith(UNIT_PX)) {
					return Float.parseFloat(pString.substring(0, pString.length() - 2));
				} else {
					return Float.parseFloat(pString);
				}
			} catch (final NumberFormatException nfe) {
				return null;
			}
		}
	}
	
	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		// TODO Auto-generated method stub
		super.characters(ch, start, length);
	}
	
	@Override
	public void endElement(String uri, String localName, String qName)
			throws SAXException {
		// TODO Auto-generated method stub
		super.endElement(uri, localName, qName);
	}
	
	@Override
	public void endDocument() throws SAXException {
		// TODO Auto-generated method stub
		super.endDocument();
	}
}
