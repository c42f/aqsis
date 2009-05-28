// Aqsis
// Copyright (C) 1997 - 2007, Paul C. Gregory
//
// Contact: pgregory@aqsis.org
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
 *
 * \brief RIB request handler and parser speed test.
 *
 * This is a small program for testing the speed of the RIB parser and RIB
 * request handler implementation.  It reads a RIB stream, recognises the
 * requesets and then promptly discards them all with empty implementations of
 * the RI functions.
 *
 * \author Chris Foster [chris42f (at) g mail (d0t) com]
 */


#include <cstdlib>
#include <fstream>

#include <aqsis/iribparser.h>
#include "ribrequesthandler.h"
#include <aqsis/ri/ri.h>

static Aqsis::IqRibParser* g_parser = 0;


// Open and read the file as a RIB stream, discarding all content.
void readFile(const char* fileName, Aqsis::IqRibParser& parser)
{
	std::ifstream inFile(fileName, std::ios::binary);
	if(!inFile)
	{
		std::cerr << "Could not open input file " << fileName << "\n";
		return;
	}

	parser.pushInput(inFile, fileName);
	bool parsing = true;
	while(parsing)
	{
		try
		{
			parsing = parser.parseNextRequest();
		}
		catch(Aqsis::XqParseError& e)
		{
			std::cerr << "ERROR:" << e.what() << "\n";
		}
	}
	parser.popInput();
}


// ReadArchive without search path support.
AQSIS_RI_SHARE RtVoid RiReadArchiveV(RtToken name, RtArchiveCallback callback, RtInt count,
		RtToken tokens[], RtPointer values[])
{
	readFile(name, *g_parser);
}


int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << "file.rib\n";
		std::exit(1);
	}

	boost::shared_ptr<Aqsis::IqRibRequestHandler> handler(
		new Aqsis::CqRibRequestHandler());
	boost::shared_ptr<Aqsis::IqRibParser> parser =
		Aqsis::IqRibParser::create(handler);
	g_parser = parser.get();

	readFile(argv[1], *parser);
}


//==============================================================================
// Dummy definitions for all RI symbols.  The RI functions do nothing.

AQSIS_RI_SHARE RtBasis RiBezierBasis =
{
	{ -1,  3, -3, 1},
	{  3, -6,  3, 0},
	{ -3,  3,  0, 0},
	{  1,  0,  0, 0}
};
AQSIS_RI_SHARE RtBasis RiBSplineBasis =
{
	{ -1.0 / 6,  3.0 / 6, -3.0 / 6, 1.0 / 6},
	{  3.0 / 6, -6.0 / 6,  3.0 / 6, 0.0 / 6},
	{ -3.0 / 6,  0.0 / 6,  3.0 / 6, 0.0 / 6},
	{  1.0 / 6,  4.0 / 6,  1.0 / 6, 0.0 / 6}
};
AQSIS_RI_SHARE RtBasis RiCatmullRomBasis =
{
	{ -1.0 / 2,  3.0 / 2, -3.0 / 2,  1.0 / 2},
	{  2.0 / 2, -5.0 / 2,  4.0 / 2, -1.0 / 2},
	{ -1.0 / 2,  0.0 / 2,  1.0 / 2,  0.0 / 2},
	{  0.0 / 2,  2.0 / 2,  0.0 / 2,  0.0 / 2}
};
AQSIS_RI_SHARE RtBasis RiHermiteBasis =
{
	{  2,  1, -2,  1},
	{ -3, -2,  3, -1},
	{  0,  1,  0,  0},
	{  1,  0,  0,  0}
};
AQSIS_RI_SHARE RtBasis RiPowerBasis =
{
	{ 1, 0, 0, 0},
	{ 0, 1, 0, 0},
	{ 0, 0, 1, 0},
	{ 0, 0, 0, 1}
};


// Empty implementations of all required Ri* functions.
// Autogenerated via XSLT, with those functions actually used above commented out.

AQSIS_RI_SHARE RtToken RiDeclare(RtString name, RtString declaration) {return "";}
AQSIS_RI_SHARE RtVoid RiBegin(RtToken name) {}
AQSIS_RI_SHARE RtVoid RiEnd() {}
AQSIS_RI_SHARE RtContextHandle RiGetContext() {return reinterpret_cast<RtContextHandle>(1);}
AQSIS_RI_SHARE RtVoid RiContext(RtContextHandle handle) {}
AQSIS_RI_SHARE RtVoid RiFrameBegin(RtInt number) {}
AQSIS_RI_SHARE RtVoid RiFrameEnd() {}
AQSIS_RI_SHARE RtVoid RiWorldBegin() {}
AQSIS_RI_SHARE RtVoid RiWorldEnd() {}
AQSIS_RI_SHARE RtVoid RiIfBegin(RtString condition) {}
AQSIS_RI_SHARE RtVoid RiElseIf(RtString condition) {}
AQSIS_RI_SHARE RtVoid RiElse() {}
AQSIS_RI_SHARE RtVoid RiIfEnd() {}
AQSIS_RI_SHARE RtVoid RiFormat(RtInt xresolution, RtInt yresolution, RtFloat pixelaspectratio) {}
AQSIS_RI_SHARE RtVoid RiFrameAspectRatio(RtFloat frameratio) {}
AQSIS_RI_SHARE RtVoid RiScreenWindow(RtFloat left, RtFloat right, RtFloat bottom, RtFloat top) {}
AQSIS_RI_SHARE RtVoid RiCropWindow(RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax) {}
AQSIS_RI_SHARE RtVoid RiProjectionV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiClipping(RtFloat cnear, RtFloat cfar) {}
AQSIS_RI_SHARE RtVoid RiClippingPlane(RtFloat x, RtFloat y, RtFloat z, RtFloat nx, RtFloat ny, RtFloat nz) {}
AQSIS_RI_SHARE RtVoid RiDepthOfField(RtFloat fstop, RtFloat focallength, RtFloat focaldistance) {}
AQSIS_RI_SHARE RtVoid RiShutter(RtFloat opentime, RtFloat closetime) {}
AQSIS_RI_SHARE RtVoid RiPixelVariance(RtFloat variance) {}
AQSIS_RI_SHARE RtVoid RiPixelSamples(RtFloat xsamples, RtFloat ysamples) {}
AQSIS_RI_SHARE RtVoid RiPixelFilter(RtFilterFunc function, RtFloat xwidth, RtFloat ywidth) {}
AQSIS_RI_SHARE RtVoid RiExposure(RtFloat gain, RtFloat gamma) {}
AQSIS_RI_SHARE RtVoid RiImagerV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiQuantize(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ditheramplitude) {}
AQSIS_RI_SHARE RtVoid RiDisplayV(RtToken name, RtToken type, RtToken mode, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtFloat RiGaussianFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiBoxFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiMitchellFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiTriangleFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiCatmullRomFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiSincFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiDiskFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtFloat RiBesselFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {return 0;}
AQSIS_RI_SHARE RtVoid RiHiderV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiColorSamples(RtInt N, RtFloat nRGB[], RtFloat RGBn[]) {}
AQSIS_RI_SHARE RtVoid RiRelativeDetail(RtFloat relativedetail) {}
AQSIS_RI_SHARE RtVoid RiOptionV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiAttributeBegin() {}
AQSIS_RI_SHARE RtVoid RiAttributeEnd() {}
AQSIS_RI_SHARE RtVoid RiColor(RtColor Cq) {}
AQSIS_RI_SHARE RtVoid RiOpacity(RtColor Os) {}
AQSIS_RI_SHARE RtVoid RiTextureCoordinates(RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2, RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4) {}
AQSIS_RI_SHARE RtLightHandle RiLightSourceV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {return reinterpret_cast<RtLightHandle>(1);}
AQSIS_RI_SHARE RtLightHandle RiAreaLightSourceV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {return reinterpret_cast<RtLightHandle>(1);}
AQSIS_RI_SHARE RtVoid RiIlluminate(RtLightHandle light, RtBoolean onoff) {}
AQSIS_RI_SHARE RtVoid RiSurfaceV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiDeformationV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiDisplacementV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiAtmosphereV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiInteriorV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiExteriorV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiShaderLayerV(RtToken type, RtToken name, RtToken layername, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiConnectShaderLayers(RtToken type, RtToken layer1, RtToken variable1, RtToken layer2, RtToken variable2) {}
AQSIS_RI_SHARE RtVoid RiShadingRate(RtFloat size) {}
AQSIS_RI_SHARE RtVoid RiShadingInterpolation(RtToken type) {}
AQSIS_RI_SHARE RtVoid RiMatte(RtBoolean onoff) {}
AQSIS_RI_SHARE RtVoid RiBound(RtBound bound) {}
AQSIS_RI_SHARE RtVoid RiDetail(RtBound bound) {}
AQSIS_RI_SHARE RtVoid RiDetailRange(RtFloat offlow, RtFloat onlow, RtFloat onhigh, RtFloat offhigh) {}
AQSIS_RI_SHARE RtVoid RiGeometricApproximation(RtToken type, RtFloat value) {}
AQSIS_RI_SHARE RtVoid RiOrientation(RtToken orientation) {}
AQSIS_RI_SHARE RtVoid RiReverseOrientation() {}
AQSIS_RI_SHARE RtVoid RiSides(RtInt nsides) {}
AQSIS_RI_SHARE RtVoid RiIdentity() {}
AQSIS_RI_SHARE RtVoid RiTransform(RtMatrix transform) {}
AQSIS_RI_SHARE RtVoid RiConcatTransform(RtMatrix transform) {}
AQSIS_RI_SHARE RtVoid RiPerspective(RtFloat fov) {}
AQSIS_RI_SHARE RtVoid RiTranslate(RtFloat dx, RtFloat dy, RtFloat dz) {}
AQSIS_RI_SHARE RtVoid RiRotate(RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz) {}
AQSIS_RI_SHARE RtVoid RiScale(RtFloat sx, RtFloat sy, RtFloat sz) {}
AQSIS_RI_SHARE RtVoid RiSkew(RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1, RtFloat dx2, RtFloat dy2, RtFloat dz2) {}
AQSIS_RI_SHARE RtVoid RiCoordinateSystem(RtToken space) {}
AQSIS_RI_SHARE RtVoid RiCoordSysTransform(RtToken space) {}
AQSIS_RI_SHARE RtPoint* RiTransformPoints(RtToken fromspace, RtToken tospace, RtInt npoints, RtPoint points[]) {return 0;}
AQSIS_RI_SHARE RtVoid RiTransformBegin() {}
AQSIS_RI_SHARE RtVoid RiTransformEnd() {}
AQSIS_RI_SHARE RtVoid RiResourceV(RtToken handle, RtToken type, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiResourceBegin() {}
AQSIS_RI_SHARE RtVoid RiResourceEnd() {}
AQSIS_RI_SHARE RtVoid RiAttributeV(RtToken name, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiPolygonV(RtInt nvertices, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiGeneralPolygonV(RtInt nloops, RtInt nverts[], RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiPointsPolygonsV(RtInt npolys, RtInt nverts[], RtInt verts[], RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiPointsGeneralPolygonsV(RtInt npolys, RtInt nloops[], RtInt nverts[], RtInt verts[], RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiBasis(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep) {}
AQSIS_RI_SHARE RtVoid RiPatchV(RtToken type, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiPatchMeshV(RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiNuPatchV(RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat vknot[], RtFloat vmin, RtFloat vmax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiTrimCurve(RtInt nloops, RtInt ncurves[], RtInt order[], RtFloat knot[], RtFloat min[], RtFloat max[], RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[]) {}
AQSIS_RI_SHARE RtVoid RiSubdivisionMeshV(RtToken scheme, RtInt nfaces, RtInt nvertices[], RtInt vertices[], RtInt ntags, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiSphereV(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiConeV(RtFloat height, RtFloat radius, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiCylinderV(RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiHyperboloidV(RtPoint point1, RtPoint point2, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiParaboloidV(RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiDiskV(RtFloat height, RtFloat radius, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiTorusV(RtFloat majorrad, RtFloat minorrad, RtFloat phimin, RtFloat phimax, RtFloat thetamax, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiPointsV(RtInt npoints, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiCurvesV(RtToken type, RtInt ncurves, RtInt nvertices[], RtToken wrap, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiBlobbyV(RtInt nleaf, RtInt ncode, RtInt code[], RtInt nflt, RtFloat flt[], RtInt nstr, RtToken str[], RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiProcedural(RtPointer data, RtBound bound, RtProcSubdivFunc refineproc, RtProcFreeFunc freeproc) {}
AQSIS_RI_SHARE RtVoid RiProcFree(RtPointer data) {}
AQSIS_RI_SHARE RtVoid RiProcDelayedReadArchive(RtPointer data, RtFloat detail) {}
AQSIS_RI_SHARE RtVoid RiProcRunProgram(RtPointer data, RtFloat detail) {}
AQSIS_RI_SHARE RtVoid RiProcDynamicLoad(RtPointer data, RtFloat detail) {}
AQSIS_RI_SHARE RtVoid RiGeometryV(RtToken type, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiSolidBegin(RtToken type) {}
AQSIS_RI_SHARE RtVoid RiSolidEnd() {}
AQSIS_RI_SHARE RtObjectHandle RiObjectBegin() {return reinterpret_cast<RtObjectHandle>(1);}
AQSIS_RI_SHARE RtVoid RiObjectEnd() {}
AQSIS_RI_SHARE RtVoid RiObjectInstance(RtObjectHandle handle) {}
AQSIS_RI_SHARE RtVoid RiMotionBegin(RtInt N,  ...) {}
AQSIS_RI_SHARE RtVoid RiMotionBeginV(RtInt N, RtFloat times[]) {}
AQSIS_RI_SHARE RtVoid RiMotionEnd() {}
AQSIS_RI_SHARE RtVoid RiMakeTextureV(RtString imagefile, RtString texturefile, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiMakeBumpV(RtString imagefile, RtString bumpfile, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiMakeLatLongEnvironmentV(RtString imagefile, RtString reflfile, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiMakeCubeFaceEnvironmentV(RtString px, RtString nx, RtString py, RtString ny, RtString pz, RtString nz, RtString reflfile, RtFloat fov, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiMakeShadowV(RtString picfile, RtString shadowfile, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiMakeOcclusionV(RtInt npics, RtString picfiles[], RtString shadowfile, RtInt count, RtToken tokens[], RtPointer values[]) {}
AQSIS_RI_SHARE RtVoid RiErrorHandler(RtErrorFunc handler) {}
AQSIS_RI_SHARE RtVoid RiErrorIgnore(RtInt code, RtInt severity, RtString message) {}
AQSIS_RI_SHARE RtVoid RiErrorPrint(RtInt code, RtInt severity, RtString message) {}
AQSIS_RI_SHARE RtVoid RiErrorAbort(RtInt code, RtInt severity, RtString message) {}
AQSIS_RI_SHARE RtVoid RiArchiveRecord(RtToken type, char * format,  ...) {}
//AQSIS_RI_SHARE RtVoid RiReadArchiveV(RtToken name, RtArchiveCallback callback, RtInt count, RtToken tokens[], RtPointer values[]) {}