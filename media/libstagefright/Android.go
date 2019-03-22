package libstagefright

import (
        "android/soong/android"
        "android/soong/cc"
        "fmt"
        "strings"
)

func init() {
	fmt.Println("libstagefright want to conditional Compile")
	android.RegisterModuleType("cc_libstagefright", DefaultsFactory)
}

func DefaultsFactory() (android.Module) {
    module := cc.DefaultsFactory()
    android.AddLoadHook(module, Defaults)
    return module
}

func Defaults(ctx android.LoadHookContext) {
    type props struct {
        Cflags []string
    }
    p := &props{}
    p.Cflags = globalDefaults(ctx)
    ctx.AppendProperties(p)
}
func globalDefaults(ctx android.BaseContext) ([]string) {
	var cppflags []string
	if (strings.EqualFold(ctx.AConfig().Getenv("TARGET_PRODUCT"),"rk3368")) {
        cppflags = append(cppflags,"-DRK3368=1")
	}
	return cppflags
}
