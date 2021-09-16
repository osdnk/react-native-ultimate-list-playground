import { requireNativeComponent, ViewProps } from 'react-native';

export const RecyclerListView = requireNativeComponent<
  ViewProps & { count: number; animatedRuntimeAddress: number }
>('RecyclerListView');
export const RecyclerRow = requireNativeComponent('RecyclerRow');
export const UltraFastTextWrapper = requireNativeComponent(
  'UltraFastTextWrapper'
);
