# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
#
# ##### END GPL LICENSE BLOCK #####

# <pep8 compliant>

# To support reload properly, try to access a package var, if it's there, reload everything
if "bpy" in locals():
    import imp
    if "import_obj" in locals():
        imp.reload(import_obj)
    if "export_obj" in locals():
        imp.reload(export_obj)


import bpy
from bpy.props import *
from io_utils import ExportHelper, ImportHelper


class ExportOBJ(bpy.types.Operator, ExportHelper):
    '''Save a Wavefront OBJ File'''

    bl_idname = "export_scene.obj"
    bl_label = 'Export ofxGLM'
    bl_options = {'PRESET'}

    filename_ext = ".obj"
    filter_glob = StringProperty(default="*.obj;*.mtl", options={'HIDDEN'})

    # List of operator properties, the attributes will be assigned
    # to the class instance from the operator settings before calling.

    # context group
    use_selection = BoolProperty(name="Selection Only", description="Export selected objects only", default=False)
    use_all_scenes = BoolProperty(name="All Scenes", description="", default=False)
    use_animation = BoolProperty(name="Animation", description="", default=False)

    # object group
    use_modifiers = BoolProperty(name="Apply Modifiers", description="Apply modifiers (preview resolution)", default=True)
    use_rotate_x90 = BoolProperty(name="Rotate X90", description="", default=True)

    # extra data group
    use_edges = BoolProperty(name="Edges", description="", default=True)
    use_normals = BoolProperty(name="Normals", description="", default=True)
    use_hq_normals = BoolProperty(name="High Quality Normals", description="", default=True)
    use_uvs = BoolProperty(name="UVs", description="", default=True)
    use_materials = BoolProperty(name="Materials", description="", default=True)
    copy_images = BoolProperty(name="Copy Images", description="", default=True)
    use_triangles = BoolProperty(name="Triangulate", description="", default=True)
    use_vertex_groups = BoolProperty(name="Polygroups", description="", default=False)
    use_nurbs = BoolProperty(name="Nurbs", description="", default=False)

    # grouping group
    use_blen_objects = BoolProperty(name="Objects as OBJ Objects", description="", default=True)
    group_by_object = BoolProperty(name="Objects as OBJ Groups ", description="", default=False)
    group_by_material = BoolProperty(name="Material Groups", description="", default=False)
    keep_vertex_order = BoolProperty(name="Keep Vertex Order", description="", default=False)

    def execute(self, context):
        from . import export_obj
        return export_obj.save(self, context, **self.as_keywords(ignore=("check_existing", "filter_glob")))


def menu_func_import(self, context):
    self.layout.operator(ImportOBJ.bl_idname, text="ofxGLM (.obj)")


def menu_func_export(self, context):
    self.layout.operator(ExportOBJ.bl_idname, text="ofxGLM (.obj)")


def register():
    bpy.types.INFO_MT_file_export.append(menu_func_export)

# bpy.types.INFO_MT_file_import.append(menu_func_import)

def unregister():
    bpy.types.INFO_MT_file_export.remove(menu_func_export)

#bpy.types.INFO_MT_file_import.remove(menu_func_import)
# CONVERSION ISSUES
# - matrix problem
# - duplis - only tested dupliverts
# - all scenes export
# + normals calculation

if __name__ == "__main__":
    register()
